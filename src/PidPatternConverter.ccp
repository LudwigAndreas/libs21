//
// Created by Ludwig Andreas on 25.07.2023.
//

#include "logger/parse/converters/PidPatternConverter.h"

namespace s21::parse {

PidPatternConverter::PidPatternConverter(std::vector<String> &options)
    : PatternConverter(options) {
  name_ = "Pid";
}

std::shared_ptr<PatternConverter> PidPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<PatternConverter>(options);
    return def;
  }
  return std::make_shared<PatternConverter>(options);
}

void PidPatternConverter::format(const LoggingEvent &event,
                                 String &to_append_to) const {
  (void) event;
  to_append_to.append(std::to_string(LoggingEvent::GetPid()));
}

}