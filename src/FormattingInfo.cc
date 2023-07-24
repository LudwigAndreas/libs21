//
// Created by Ludwig Andreas on 20.07.2023.
//

#include "logger/parse/FormattingInfo.h"

#include <climits>

namespace s21::parse {

FormattingInfo::FormattingInfo(const bool left_align,
                               const int min_length,
                               const int max_length) :
    left_align_(left_align),
    min_length_(min_length),
    max_length_(max_length) {}

FormattingInfo FormattingInfo::getDefault() {
  static FormattingInfo def = FormattingInfo(false, 0, INT_MAX);
  return def;
}

bool FormattingInfo::isLeftAligned() const {
  return left_align_;
}

int FormattingInfo::getMinLength() const {
  return min_length_;
}

int FormattingInfo::getMaxLength() const {
  return max_length_;
}
FormattingInfo::FormattingInfo() : left_align_(false), min_length_(0),
max_length_(INT_MAX) {}

void FormattingInfo::format(const int field_start, String &buffer) const {
  int raw_length = int(buffer.length() - field_start);
  if (raw_length > max_length_) {
    buffer.erase(buffer.begin() + field_start,
                 buffer.begin() + field_start + (raw_length - max_length_));
  } else if (raw_length < min_length_) {
    if (left_align_) {
      buffer.append(min_length_ - raw_length, ' ');
    } else {
      buffer.insert(field_start, min_length_ - raw_length, ' ');
    }
  }
}
}