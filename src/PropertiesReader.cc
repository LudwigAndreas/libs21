//
// Created by Ludwig Andreas on 15.07.2023.
//

#include "logger/PropertiesReader.h"
#include "s21.h"

s21::PropertiesReader::PropertiesReader() {
  this->file_path = "resources/application.properties";
  updateProperties();
}

s21::PropertiesReader::~PropertiesReader() {
}

bool s21::PropertiesReader::updateProperties() {
  if (!this->file_path.empty()) {
    this->properties = s21::properties_reader(file_path);
  }
  return true;
}

s21::PropertiesReader::PropertiesReader(const std::string& file_path) {
  this->file_path = file_path;
  updateProperties();
}

void s21::PropertiesReader::set_path(const std::string file_path) {
  this->file_path = file_path;
}

std::map<std::string, std::string> s21::PropertiesReader::get_properties() {
  return this->properties;
}

std::string s21::PropertiesReader::get_property(const std::string& key) {
  return this->properties.at(key);
}

void s21::PropertiesReader::update() {
  updateProperties();
}
