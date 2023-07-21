//
// Created by Ludwig Andreas on 20.07.2023.
//

#include "FormattingInfo.h"

namespace s21::parse {

FormattingInfo::FormattingInfo(const bool left_align,
                               const int min_length,
                               const int max_length) :
    left_align_(left_align),
    min_length_(min_length),
    max_length_(max_length) {}

FormattingInfo FormattingInfo::getDefault() {
  static FormattingInfo def = FormattingInfo(false, 0, 2147483647);
  return def;
}

bool FormattingInfo::isLeftAligned() {
  return left_align_;
}

int FormattingInfo::getMinLength() {
  return min_length_;
}

int FormattingInfo::getMaxLength() {
  return max_length_;
}

}