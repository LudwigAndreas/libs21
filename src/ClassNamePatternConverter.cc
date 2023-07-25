//
// Created by Ludwig Andreas on 22.07.2023.
//

#include <logger/parse/LoggingEvent.h>
#include <logger/parse/converters/ClassNamePatternConverter.h>

namespace s21::parse {
std::shared_ptr<PatternConverter> ClassNamePatternConverter::newInstance(
    std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter>  def = std::make_shared<ClassNamePatternConverter>(options);
    return def;
  }
  return std::make_shared<ClassNamePatternConverter>(options);
}
ClassNamePatternConverter::ClassNamePatternConverter(std::vector<
    String> &options) : PatternConverter(options) {
  name_ = "Class name";
}

void ClassNamePatternConverter::format(const LoggingEvent &event,
                                                   String &to_append_to) const {
  to_append_to.append(event.getClassName());
}
}