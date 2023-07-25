#ifndef S21_INCLUDE_LOGGER_LOGGER_MACROS_H_
#define S21_INCLUDE_LOGGER_LOGGER_MACROS_H_

#define LOG(log_obj, level, message) { \
  std::stringstream oss_;                  \
  oss_ << message;                         \
  log_obj->Log(level, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_TRACE(log_obj, message) { \
  std::stringstream oss_;    \
  oss_ << message;           \
  log_obj->Log(s21::diagnostic::LogLevel::Trace, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_DEBUG(log_obj, message) \
  {                        \
  std::stringstream oss_;  \
  oss_ << message;         \
  log_obj->Log(s21::diagnostic::LogLevel::Debug, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_INFO(log_obj, message) \
  {                       \
  std::stringstream oss_; \
  oss_ << message;        \
  log_obj->Log(s21::diagnostic::LogLevel::Info, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_WARN(log_obj, message) \
  {                       \
  std::stringstream oss_; \
  oss_ << message;        \
  log_obj->Log(s21::diagnostic::LogLevel::Warn, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_ERROR(log_obj, message) \
  {                        \
  std::stringstream oss_;  \
  oss_ << message;         \
  log_obj->Log(s21::diagnostic::LogLevel::Error, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_FATAL(log_obj, message) \
  {                        \
  std::stringstream oss_;  \
  oss_ << message;         \
  log_obj->Log(s21::diagnostic::LogLevel::Fatal, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }


#endif //S21_INCLUDE_LOGGER_LOGGER_MACROS_H_
