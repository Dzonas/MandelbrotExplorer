#ifndef OPENGL_TUTORIAL_SRC_SHADER_H
#define OPENGL_TUTORIAL_SRC_SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
  GLuint program = 0;

  static GLuint link(GLuint vertex_shader, GLuint fragment_shader);
  static GLuint compile(GLenum shader_type, const GLchar *source);
public:
  void init(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
  void destroy();
  void use() { glUseProgram(program); }
  void set_mat4(const std::string &name, glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
  }
  void set_vec3(const std::string &name, glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(value));
  }
  void set_vec3(const std::string& name, const float value[], const unsigned int count = 1) const {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), count, value);
    auto error = glGetError();
  }
  void set_mat3(const std::string &name, glm::mat3 &value) {
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
  }

  void set_float_array(const std::string &name, unsigned int count, const float *value) {
      glUniform1fv(glGetUniformLocation(program, name.c_str()), count, value);
  }
};

#endif //OPENGL_TUTORIAL_SRC_SHADER_H
