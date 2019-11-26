#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <colors.h>

#define SHADER_DEBUG

#ifdef SHADER_DEBUG
#define SHADER_DEBUG_PRINT_FILE
#define SHADER_DEBUG_PRINT_PATH
#define SHADER_DEBUG_PRINT_COMPILE
#endif

class Shader {
private:
    GLuint id;

public:
    explicit Shader(const char *vertex_shader_path,
        const char *fragment_shader_path);
    GLuint create(const char *vertex_shader_path,
        const char *fragment_shader_path);
    void use();
    GLuint getId();
    template <typename T> void setValue(const char *name, T &value);
    void setVec3(const char *name, float x, float y, float z);
    void setMat4(const char *name, const glm::mat4 &mat);
};

#endif /* SHADER_H */
