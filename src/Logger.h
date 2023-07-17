//
// Created by Ludwig Andreas on 17.07.2023.
//

#ifndef S21_SRC_LOGGER_H_
#define S21_SRC_LOGGER_H_

#include <utility>
#include <vector>
#include <string>
#include <iostream>

#include <time.h>

#define WRITELOG(logObj, level, message) logObj.Log(level, __FILEW__, __LINE__, __FUNCTIONW__, message);

typedef std::wostream ToStream;
typedef std::string String;



namespace s21::diagnostic {

enum class LogLevel {
  Trace,
  Debug,
  Info,
  Warn,
  Error,
  Fatal
};

enum class LogItem {
  Filename = 0x1,
  LineNumber = 0x2,
  Function = 0x4,
  DateTime = 0x8,
  ThreadId = 0x10,
  LoggerName = 0x20,
  LogLevel = 0x40
};

template<class ThreadingProtection>
class Logger {
 private:
  struct StreamInfo {
    ToStream *p_stream;
    bool owned;
    LogLevel level;

    StreamInfo(ToStream *p_stream, bool owned, LogLevel level) :
        p_stream(p_stream),
        owned(owned),
        level(level) {}
  };

  const char separator = ' ';
  const std::string datetime_format = "%Y/%m/%d.%X";

 public:
  Logger(s21::diagnostic::LogLevel level, String name,
         int loggableItems =
         static_cast<int>(LogItem::Function) |
             static_cast<int>(LogItem::LineNumber) |
             static_cast<int>(LogItem::DateTime) |
             static_cast<int>(LogItem::LoggerName) |
             static_cast<int>(LogItem::LogLevel))
      : level_(level), name_(std::move(name)), loggable_item_(loggableItems) {}

  ~Logger() = default;

  void AddOutputStream(ToStream &os, bool own, LogLevel level) {
    AddOutputStream(&os, own, level);
  }

  void AddOutputStream(ToStream &os, bool own) {
    AddOutputStream(os, own, level_);
  }

  void AddOutputStream(ToStream *os, bool own) {
    AddOutputStream(os, own, level_);
  }

  void AddOutputStream(ToStream *os, bool own, LogLevel level) {
    StreamInfo stream_info(os, own, level);
    output_streams_.push_back(stream_info);
  }

  void ClearOutputStream() {
    for (auto iter = output_streams_.begin(); iter < output_streams_.end(); ++iter) {
      if (iter->owned)
        delete iter->p_stream;
    }
  }

  void Log(LogLevel level, String file, int line, String func, String message) {
    mtx_.lock();

    for (auto iter = output_streams_.begin(); iter < output_streams_.end(); ++iter) {
      if (level < iter->level) {
        continue;
      }
      bool written = false;
      ToStream *p_stream = iter->p_stream;

      if (loggable_item_ & static_cast<int>(LogItem::DateTime))
        written = writeDatetime(written, p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::ThreadId))
        written = write<int>(std::this_thread::get_id(), written, p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::LoggerName))
        written = write<String>(name_.c_str(), written, p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::LogLevel)) {
        char[6] str_level;
        logLevelToString(level, str_level);
        written = write<String>(str_level, written, p_stream);
      }
      if (loggable_item_ & static_cast<int>(LogItem::Function))
        written = write<String>(func.c_str(), written, p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::Filename))
        written = write<String>(file, written, p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::LineNumber))
        written = write<String>(line, written, p_stream);

      written = write<String>(message, written, p_stream);

      if (written) {
        (*p_stream) << std::endl;
        p_stream->flush();
      }
    }
    mtx_.unlock();
  }

 private:
  int loggable_item_;
  LogLevel level_;
  String name_;
  std::vector<StreamInfo> output_streams_;
  ThreadingProtection threading_protection_;
  std::mutex mtx_;

  template<class T>
  inline bool write(T data, bool written, ToStream *wostream) {
    if (written) {
      (*wostream) << separator;
    }

    (*wostream) << data;
    return true;
  }

  inline bool writeDatetime(bool written, ToStream *wostream) {
    if (written) {
      (*wostream) << separator;
    }

    time_t now = time(nullptr);
    struct tm tstruct;
    char str_date_time[datetime_format.size()];

    tstruct = *std::localtime(&now);
    strftime(str_date_time, sizeof(str_date_time), datetime_format.c_str(), &tstruct);
    (*wostream) << str_date_time;
    return true;
  }

  void logLevelToString(LogLevel level, char *str_level) {
    switch (level) {
      case LogLevel::Fatal:
        std::strncpy("FATAL", str_level, 6);
        break;
      case LogLevel::Error:
        std::strncpy("ERROR", str_level, 6);
        break;
      case LogLevel::Warn:
        std::strncpy(" WARN", str_level, 6);
        break;
      case LogLevel::Info:
        std::strncpy(" INFO", str_level, 6);
        break;
      case LogLevel::Debug:
        std::strncpy("DEBUG", str_level, 6);
        break;
      case LogLevel::Trace:
        std::strncpy("TRACE", str_level, 6);
        break;
    }
  }

};
}

#endif //S21_SRC_LOGGER_H_
