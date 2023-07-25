//
// Created by Ludwig Andreas on 25.07.2023.
//

#include <map>

#include "logger/LoggerConfigurator.h"


namespace s21::diagnostic {

void LoggerConfigurator::configure(PatternLayout &&layout) {

  String layout_arg = layout.getConversionPattern();
  PatternLayout final_layout;
  if (layout_arg.empty()) {
    static const String
        pattern = "%d{%Y-%m-%d %X} %5.5p %-5P --- [%M] %-25.40F : %m%n";
    final_layout = PatternLayout(pattern);
  } else {
    final_layout = layout.getConversionPattern();
  }
  auto logger_repo = Logger::GetLoggerRepo();
  for (auto it = logger_repo.begin();
       it != logger_repo.end(); ++it) {
    if (std::next(it) == logger_repo.end())
      it->second->SetPatternLayout(std::move(final_layout));
    else
      it->second->SetPatternLayout(final_layout.GetCopy());
    it->second->AddOutputStream(std::cout, false);
  }
}

}