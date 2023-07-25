//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/MessagePatternConverter.h"

namespace s21::parse {

MessagePatternConverter::MessagePatternConverter(std::vector<String> &options)
    : PatternConverter(options) {
  name_ = "Message";
}

std::shared_ptr<PatternConverter> MessagePatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<MessagePatternConverter>(options);
    return def;
  }
  return std::make_shared<MessagePatternConverter>(options);
}

void MessagePatternConverter::format(const LoggingEvent &event,
                                     String &to_append_to) const {
  to_append_to.append(event.getMessage());
}

}
