//
// Created by Ludwig Andreas on 21.07.2023.
//

#include "logger/parse/converters/PatternConverter.h"

#include <utility>


namespace s21::parse {
PatternConverter::PatternConverter(String &name,
                                               std::vector<String> &options) :
    options_(std::move(options)),
    name_(name) {}

PatternConverter::~PatternConverter() = default;

void PatternConverter::setOptions(const std::vector<String> &options) {
  options_ = options;
}
void PatternConverter::setName(const String &name) {
  name_ = name;
}
const std::vector<String> &PatternConverter::getOptions() const {
  return options_;
}
const String &PatternConverter::getName() const {
  return name_;
}
PatternConverter::PatternConverter(const std::vector<String> &options) {
  this->options_ = options;
}
}