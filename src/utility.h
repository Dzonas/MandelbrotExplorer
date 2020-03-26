#ifndef OPENGL_TUTORIAL_SRC_UTILITY_H
#define OPENGL_TUTORIAL_SRC_UTILITY_H

#include <string>
#include <sstream>
#include <fstream>

std::string load_file(const std::string& path) {
  auto ss = std::ostringstream{};
  std::ifstream file(path);

  if(!file.is_open())
      throw std::runtime_error("can't open file: " + path);

  std::string a;
  ss << file.rdbuf();
  return ss.str();
}

#endif //OPENGL_TUTORIAL_SRC_UTILITY_H
