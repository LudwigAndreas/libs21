//
// Created by Ludwig Andreas on 20.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSER_FORMATTINGINFO_H_
#define S21_INCLUDE_LOGGER_PARSER_FORMATTINGINFO_H_

#include "logger/logger_type.h"

namespace s21::parse {
class FormattingInfo {
 private:
  bool left_align_{};
  int min_length_{};
  int max_length_{};

 public:
  FormattingInfo();

  ~FormattingInfo() = default;

  FormattingInfo(bool left_align, int min_length, int max_length);

  void format(int field_start, String& buffer) const;

  static FormattingInfo getDefault();

  bool isLeftAligned() const;

  int getMinLength() const;

  int getMaxLength() const;
};
}

#endif //S21_INCLUDE_LOGGER_PARSER_FORMATTINGINFO_H_
