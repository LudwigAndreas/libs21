//
// Created by Ludwig Andreas on 21.07.2023.
//

#include "logger/parse/PatternConverter.h"

#include <utility>


namespace s21::parse {
PatternConverter::PatternConverter(String name,
                                               std::vector<String> options,
                                               FormattingInfo formatting_info) :
    options_(std::move(options)),
    formatting_info_(formatting_info),
    name_(name) {}

PatternConverter::~PatternConverter() {}

void PatternConverter::setFormattingInfo(const FormattingInfo &formatting_info) {
  formatting_info_ = formatting_info;
}
void PatternConverter::setOptions(const std::vector<String> &options) {
  options_ = options;
}
void PatternConverter::setName(const String &name) {
  name_ = name;
}
const std::vector<String> &PatternConverter::getOptions() const {
  return options_;
}
const FormattingInfo PatternConverter::getFormattingInfo() const {
  return formatting_info_;
}
const String &PatternConverter::getName() const {
  return name_;
}
}