#ifndef SHADER_H
#define SHADER_H

#include <sys/types.h>
#include <sys/stat.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <colors.h>

class Shader {
private:
    GLuint id;

public:
    explicit Shader(const char *vs_path, const char *fs_path);

    // shader
    GLuint createVertexShader(const char *path);
    GLuint createFragmentShader(const char *path);
    GLuint createShaderProgram(GLuint vs_id, GLuint fs_id);
    GLuint getId();
    void use();

    void setVec3(const char *name, float x, float y, float z);
    void setMat4(const char *name, const glm::mat4 &mat);

    template <typename T> void setValue(const char *name, T &value);
};

#endif /* SHADER_H */
