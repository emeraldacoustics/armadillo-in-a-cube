#ifndef _GL_HELPERS_H_
#define _GL_HELPERS_H_

#define GLH_SHADER_HEADER "#version 410 core\n"
#define GLH_STRINGIFY(x) #x
#define GLCHECK(x)                                                             \
  do {                                                                         \
    x;                                                                         \
    glh_check(__FILE__, __LINE__);                                             \
  } while (0)

void glh_check(const char *filename, uint32_t lineno);
int8_t glh_check_program_status(GLuint program_id, bool report_error);
int8_t glh_check_shader_status(GLuint shader_id, bool report_error);
GLuint glh_compile_shader_src(GLuint shader_type, const char *shader_src); 
GLuint glh_link_program(GLuint vertex_shader, GLuint geometry_shader, GLuint fragment_shader);
#endif /* _GL_HELPERS_H_ */


#ifdef _GL_HELPERS_IMPLEMENTATION_

void glh_check(const char *filename, uint32_t lineno) {
  uint32_t error = glGetError();

  if (error != GL_NO_ERROR) {
    printf("OGL Error %d at %s: %d\n", error, filename, lineno);
    exit(-1);
  }
}

int8_t glh_check_program_status(GLuint program_id, bool report_error) {
  int32_t successful_linking = 0;
  glGetProgramiv(program_id, GL_LINK_STATUS, &successful_linking);
  if (report_error && successful_linking == GL_FALSE) {
    int32_t str_length = 0;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &str_length);
    GLchar *info_log = (GLchar *)malloc(str_length);
    glGetProgramInfoLog(program_id, str_length, &str_length, info_log);
    fprintf(stderr, "[GL] Link error :\n%s\n", info_log);
    free(info_log);
    return 1;
  }
  return 0;
}

int8_t glh_check_shader_status(GLuint shader_id, bool report_error) {
  int32_t successful_linking = 0;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &successful_linking);
  if (report_error && successful_linking == GL_FALSE) {
    int32_t str_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &str_length);
    GLchar *info_log = (GLchar *)malloc(str_length);
    glGetShaderInfoLog(shader_id, str_length, &str_length, info_log);
    fprintf(stderr, "[GL] Compile error :\n%s\n", info_log);
    free(info_log);
    return 1;
  }
  return 0;
}

GLuint glh_compile_shader_src(GLuint shader_type, const char *shader_src) {
  const GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &shader_src, NULL);
  glCompileShader(shader);
  int32_t error = glh_check_shader_status(shader, true);
  if (error) {
    exit(-1);
  }
  return shader;
}

GLuint glh_link_program(GLuint vertex_shader, GLuint geometry_shader,
                        GLuint fragment_shader) {
  GLuint program = glCreateProgram();

  if (vertex_shader) {
    glAttachShader(program, vertex_shader);
  }
  if (geometry_shader) {
    glAttachShader(program, geometry_shader);
  }
  if (fragment_shader) {
    glAttachShader(program, fragment_shader);
  }

  glLinkProgram(program);

  if (vertex_shader) {
    glDetachShader(program, vertex_shader);
    glDeleteShader(vertex_shader);
  }
  if (geometry_shader) {
    glDetachShader(program, geometry_shader);
    glDeleteShader(geometry_shader);
  }
  if (fragment_shader) {
    glDetachShader(program, fragment_shader);
    glDeleteShader(fragment_shader);
  }

  glh_check_program_status(program, true);
  return program;
}

#endif /* _GL_HELPERS_IMPLEMENTATION_ */
