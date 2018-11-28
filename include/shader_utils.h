#ifndef SHADERUTILSH
#define SHADERUTILSH

#define SHADER_DEBUG
#ifdef SHADER_DEBUG
#define SHADER_DEBUG_PRINT_FILE
#define SHADER_DEBUG_PRINT_PATH
#define SHADER_DEBUG_PRINT_COMPILE
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <colors.h>

GLuint ShaderCreate(const char *vertex_shader_path, const char *fragment_shader_path);

#endif
