//
// Created by Ludwig Andreas on 17.07.2023.
//

#ifndef S21_SRC_LOGGER_H_
#define S21_SRC_LOGGER_H_

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <ctime>
#include <iomanip>
#include <map>
#include <functional>
#include <any>

#define WRITELOG(logObj, level, message) logObj.Log(level, __FILE__, __LINE__, __FUNCTION__, message);

typedef std::ostream ToStream;
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

// template accepts an IThreading successor
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

  struct Parsing {
    struct Value {
      std::string raw;
      std::string flags;
      unsigned char type;
    };

    std::string templ;
    std::vector<Value> values;

    Parsing(std::string templ) : templ(templ) {
      std::string templ_ = templ;
      int pos;
      int substr;
      std::function<Value (std::string &)> func;

      while (templ_.size() && templ_.find('%') != std::string::npos) {
        if (templ_[0] == '%')
          func = &parse_variable;
        else
          func = &parse_text;
          // pos = parse_text(templ_);
        values.push_back(func(templ_));
      }
      if (templ_.size())
        values.push_back(Value(templ_, "", '\0'));
      
      return values.size();
    }

    Value parse_variable(std::string &templ_) {
      std::string lhs;
      lhs = templ_.substr(0, 2);
      templ_ = templ_.substr(2);
      return Value(lhs, "", lhs[1]);
    }

    Value parse_text(std::string &templ_) {
      std::string lhs;
      int pos = templ_.find_first_of('%');
      // if (pos == -1)
      lhs = templ_.substr(0, pos);
      templ_ = templ_.substr(pos);
      return Value(lhs, "", '\0');
    }
  };
  std::map<unsigned char, std::function<String (std::any)>> print_funcs;
  const char separator = ' ';
  const std::string datetime_format = "%Y/%m/%d.%X";
  const std::string log_format;

 public:
  Logger(s21::diagnostic::LogLevel level, String name,
         int loggableItems =
         static_cast<int>(LogItem::Function) |
             static_cast<int>(LogItem::LineNumber) |
             static_cast<int>(LogItem::DateTime) |
             static_cast<int>(LogItem::LoggerName) |
             static_cast<int>(LogItem::LogLevel)
             ,std::string log_format_ = "%d %f:%l %p %m"
  )
      : level_(level), name_(name), loggable_item_(loggableItems), log_format(log_format_) {}

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
    threading_protection_.lock();

    for (auto iter = output_streams_.begin(); iter != output_streams_.end(); iter = std::next(iter)) {
      if (level < iter->level) {
        continue;
      }
      bool written = false;
      ToStream *p_stream = iter->p_stream;

      if (loggable_item_ & static_cast<int>(LogItem::DateTime))
        written = writeDatetime(written, p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::ThreadId)) {
        int thread_id = static_cast<int>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
        written = write < int > (thread_id, p_stream);
      }
      if (loggable_item_ & static_cast<int>(LogItem::LoggerName))
        written = write < String > (name_.c_str(), p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::LogLevel)) {
        char str_level[6];
        logLevelToString(level, str_level);
        written = write < String > (str_level, p_stream);
      }
      if (loggable_item_ & static_cast<int>(LogItem::Function))
        written = write < String > (func.c_str(), p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::Filename))
        written = write < String > (file, p_stream);
      if (loggable_item_ & static_cast<int>(LogItem::LineNumber))
        written = write < int > (line, p_stream);

      written = write < String > (message, p_stream);

      // if (written) {
        (*p_stream) << std::endl;
        // p_stream->flush();
      // }
    }
    threading_protection_.unlock();
  }

 private:
  LogLevel level_;
  String name_;
  int loggable_item_;
  std::vector<StreamInfo> output_streams_;
  ThreadingProtection threading_protection_;

  void createPrintFunctions() {
    print_funcs['p'] = [](auto p_stream, auto text) {
      std::stringstream ss;
      ss << text;

    };
  }

  template<class T>
  inline bool write(T data, ToStream *wostream) {

    (*wostream) << data;
    return true;
  }

  inline bool writeDatetime(bool written, ToStream *wostream) {
    // if (written) {
    //   (*wostream) << separator;
    // }

    time_t time = std::time(nullptr);
    auto tm = *std::localtime(&time);
    (*wostream) << std::put_time(&tm, datetime_format.c_str());
    return true;
  }

  void logLevelToString(LogLevel level, char *str_level) {

    switch (level) {
      case LogLevel::Fatal:
        std::strncpy(str_level, "FATAL", 6);
        break;
      case LogLevel::Error:
        std::strncpy(str_level, "ERROR", 6);
        break;
      case LogLevel::Warn:
        std::strncpy(str_level, " WARN", 6);
        break;
      case LogLevel::Info:
        std::strncpy(str_level, " INFO", 6);
        break;
      case LogLevel::Debug:
        std::strncpy(str_level, "DEBUG", 6);
        break;
      case LogLevel::Trace:
        std::strncpy(str_level, "TRACE", 6);
        break;
    }
  }

};
}

#endif //S21_SRC_LOGGER_H_
