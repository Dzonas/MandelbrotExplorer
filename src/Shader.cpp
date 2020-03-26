#include "Shader.h"
#include "utility.h"
#include <glad/glad.h>
#include <vector>
#include <iostream>

void Shader::init(const std::string &vertex_shader_path, const std::string &fragment_shader_path) {
  std::string vertex_shader_source = load_file(vertex_shader_path);
  std::string fragment_shader_source = load_file(fragment_shader_path);
  GLuint vertex_shader = Shader::compile(GL_VERTEX_SHADER, vertex_shader_source.c_str());
  GLuint fragment_shader = Shader::compile(GL_FRAGMENT_SHADER, fragment_shader_source.c_str());
  program = link(vertex_shader, fragment_shader);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

GLuint Shader::compile(GLenum shader_type, const GLchar *source) {
  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  GLint compile_status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

  if (compile_status != GL_TRUE) {
    GLsizei log_length;
    std::vector<GLchar> message(1024);
    glGetShaderInfoLog(shader, 1024, &log_length, &message[0]);
    throw std::runtime_error(std::string(message.begin(), message.end()));
  }

  return shader;
}

GLuint Shader::link(GLuint vertex_shader, GLuint fragment_shader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLint link_status = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &link_status);

  if (link_status != GL_TRUE) {
    GLsizei log_length;
    std::vector<GLchar> message(1024);
    glGetProgramInfoLog(program, 1024, &log_length, &message[0]);
    throw std::runtime_error(std::string(message.begin(), message.end()));
  }

  return program;
}

void Shader::destroy() {
  glDeleteProgram(program);
}
