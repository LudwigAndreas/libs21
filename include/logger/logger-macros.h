#ifndef S21_INCLUDE_LOGGER_LOGGER_MACROS_H_
#define S21_INCLUDE_LOGGER_LOGGER_MACROS_H_

#define LOG(level, message) \
  {                         \
  std::stringstream oss_;   \
  oss_ << message;          \
  logger.Log(level, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_TRACE(message) { \
  std::stringstream oss_;    \
  oss_ << message;           \
  logger.Log(s21::diagnostic::LogLevel::Trace, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_DEBUG(message) \
  {                        \
  std::stringstream oss_;  \
  oss_ << message;         \
  logger.Log(s21::diagnostic::LogLevel::Debug, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_INFO(message) \
  {                       \
  std::stringstream oss_; \
  oss_ << message;        \
  logger.Log(s21::diagnostic::LogLevel::Info, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_WARN(message) \
  {                       \
  std::stringstream oss_; \
  oss_ << message;        \
  logger.Log(s21::diagnostic::LogLevel::Warn, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_ERROR(message) \
  {                        \
  std::stringstream oss_;  \
  oss_ << message;         \
  logger.Log(s21::diagnostic::LogLevel::Error, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#define LOG_FATAL(message) \
  {                        \
  std::stringstream oss_;  \
  oss_ << message;         \
  logger.Log(s21::diagnostic::LogLevel::Fatal, __FILE__, __LINE__, __FUNCTION__, oss_.str()); }

#endif //S21_INCLUDE_LOGGER_LOGGER_MACROS_H_
