//
// Created by Ludwig Andreas on 20.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSER_FORMATTINGINFO_H_
#define S21_INCLUDE_LOGGER_PARSER_FORMATTINGINFO_H_

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

  static FormattingInfo getDefault();

  [[nodiscard]] bool isLeftAligned() const;

  [[nodiscard]] int getMinLength() const;

  [[nodiscard]] int getMaxLength() const;
};
}

#endif //S21_INCLUDE_LOGGER_PARSER_FORMATTINGINFO_H_
