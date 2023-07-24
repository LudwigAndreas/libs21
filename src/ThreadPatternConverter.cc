//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/ThreadPatternConverter.h"
namespace s21::parse {

ThreadPatternConverter::ThreadPatternConverter(std::vector<String> &options)
    : PatternConverter(options) {
  name_ = "Thread name";
}

PatternConverter *ThreadPatternConverter::newInstance(std::vector<String> options) {
  return new ThreadPatternConverter(options);
}

void ThreadPatternConverter::format(const LoggingEvent &event,
                                                String &to_append_to) const {
to_append_to.append(event.GetThreadName());
}

}