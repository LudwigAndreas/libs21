//
// Created by Ludwig Andreas on 20.07.2023.
//

#include "FormattingInfo.h"

s21::parser::FormattingInfo::FormattingInfo(const bool left_align, const int min_length, const int max_length) :
    left_align_(left_align),
    min_length_(min_length),
    max_length_(max_length) {}

s21::parser::FormattingInfo s21::parser::FormattingInfo::getDefault() {
  static FormattingInfo def = FormattingInfo(false, 0, 2147483647);
  return def;
}

bool s21::parser::FormattingInfo::isLeftAligned() {
  return left_align_;
}

int s21::parser::FormattingInfo::getMinLength() {
  return min_length_;
}

int s21::parser::FormattingInfo::getMaxLength() {
  return max_length_;
}


