//
// Created by Ludwig Andreas on 22.07.2023.
//

#include <vector>

#include "logger/parse/converters/FileLocationPatternConverter.h"
#include "logger/parse/converters/PatternConverter.h"

namespace s21::parse {

FileLocationPatternConverter::FileLocationPatternConverter(std::vector<
    String> &options)
    : PatternConverter(options) {
  name_ = "File location";
}

PatternConverter *FileLocationPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new FileLocationPatternConverter(options);
    return def;
  }
  return new FileLocationPatternConverter(options);
}

void FileLocationPatternConverter::format(const LoggingEvent &event,
                                          String &to_append_to) const {
to_append_to.append(event.GetFileName());
}

}