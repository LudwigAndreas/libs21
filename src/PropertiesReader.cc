//
// Created by Ludwig Andreas on 15.07.2023.
//

#include "PropertiesReader.h"
#include "s21.h"

s21::PropertiesReader::PropertiesReader() {
  this->file_path_ = "resources/application.properties_";
  updateProperties();
}

s21::PropertiesReader::~PropertiesReader() {
}

bool s21::PropertiesReader::updateProperties() {
  if (!this->file_path_.empty()) {
    this->properties_ = s21::properties_reader(file_path_);
  }
  return true;
}

s21::PropertiesReader::PropertiesReader(const std::string& file_path) {
  this->file_path_ = file_path;
  updateProperties();
}

void s21::PropertiesReader::SetPath(const std::string &file_path) {
  this->file_path_ = file_path;
}

std::map<std::string, std::string> s21::PropertiesReader::GetProperties() {
  return this->properties_;
}

std::string s21::PropertiesReader::GetProperty(const std::string& key) {
  return this->properties_.at(key);
}

void s21::PropertiesReader::Update() {
  updateProperties();
}
