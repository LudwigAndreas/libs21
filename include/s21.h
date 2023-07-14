#ifndef LIBFT_H
#define LIBFT_H

#include <string>
#include <vector>
#include <map>

namespace s21 {
std::string to_lower(std::string str);

std::string to_upper(std::string str);

std::vector<std::string> split(std::string s, std::string delimiter);

std::map<std::string, std::string> properties_reader(const std::string &file_path);

}

#endif //LIBFT_H
