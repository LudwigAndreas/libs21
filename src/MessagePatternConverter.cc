//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/MessagePatternConverter.h"

namespace s21::parse {

MessagePatternConverter::MessagePatternConverter(std::vector<String> &options)
    : PatternConverter(options) {
  name_ = "Message";
}

PatternConverter *MessagePatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new MessagePatternConverter(options);
    return def;
  }
  return new MessagePatternConverter(options);
}

void MessagePatternConverter::format(const LoggingEvent &event,
                                     String &to_append_to) const {
  to_append_to.append(event.getMessage());
}

}
