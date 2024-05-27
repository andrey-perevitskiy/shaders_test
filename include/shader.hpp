#ifndef SHADER_H

class Shader {
private:
    GLuint id;

public:
    explicit Shader (const char * vs_path, const char * fs_path);
    GLuint createVertexShader (const char * path);
    GLuint createFragmentShader (const char * path);
    GLuint createShaderProgram (GLuint vs_id, GLuint fs_id);
    GLuint getId ();
    void use ();
    void setVec3 (const char * name, float x, float y, float z);
    void setMat4 (const char * name, const glm::mat4 &mat);
    template <typename T> void setValue (const char * name, T &value);
};

#define SHADER_H
#endif
