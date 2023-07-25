//
// Created by Ludwig Andreas on 25.07.2023.
//

#include "logger/parse/converters/PidPatternConverter.h"

namespace s21::parse {

PidPatternConverter::PidPatternConverter(std::vector<String> &options)
    : PatternConverter(options) {
  name_ = "Pid";
}

PatternConverter *PidPatternConverter::newInstance(std::vector<String> options) {
  return new PidPatternConverter(options);
}

void PidPatternConverter::format(const LoggingEvent &event,
                                 String &to_append_to) const {
  (void) event;
  to_append_to.append(std::to_string(LoggingEvent::GetPid()));
}

}