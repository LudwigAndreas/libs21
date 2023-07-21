//
// Created by Ludwig Andreas on 21.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSER_PATTERNCONVERTER_H_
#define S21_INCLUDE_LOGGER_PARSER_PATTERNCONVERTER_H_

//struct test {
//    std::func();
//    std::vector<String> options;
//    s21::parse::FormattingInfo info;
//  };

#include <vector>
#include "FormattingInfo.h"
#include "logger/Logger.h"

namespace s21::parse {
class PatternConverter {
 protected:
  std::vector<String> options_;
  FormattingInfo formatting_info_;
  String name_;

 public:
  PatternConverter() = default;

  PatternConverter(String name, std::vector<String> options,
                   FormattingInfo formatting_info);

  virtual ~PatternConverter();

  virtual void format(String &to_append_to) const = 0;

  void setFormattingInfo(const FormattingInfo &formatting_info);

  void setOptions(const std::vector<String> &options);

  void setName(const String &name);

  const std::vector<String> &getOptions() const;

  const FormattingInfo getFormattingInfo() const;

  const String &getName() const;
};
}

#endif //S21_INCLUDE_LOGGER_PARSER_PATTERNCONVERTER_H_
