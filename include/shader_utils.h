#ifndef SHADERUTILSH
#define SHADERUTILSH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string>
#include <fstream>

GLuint ShaderCreate(const char *vertex_shader_path, const char *fragment_shader_path);

#endif
