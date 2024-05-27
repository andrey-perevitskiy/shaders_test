#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "colors.hpp"

Shader::Shader (const char * vs_path, const char * fs_path)
{
    id = createShaderProgram(
        createVertexShader(vs_path),
        createFragmentShader(fs_path)
    );
}

GLuint
Shader::createVertexShader (const char * path)
{
    FILE * f;
    struct stat fattrs;
    size_t size;
    GLchar *src;
    GLchar * log = NULL;
    GLint status;
    GLuint s_id;

    // reading
    printf("\nReading \"%s\" (vertex shader)... ", path);

    f = fopen(path, "r");
    if (!f) {
		printf("%s", CRED);
        printf("failed!\n");
		printf("%s", CDFT);

        return 0;
    }

    // get size of the file
    if (stat(path, &fattrs) < 0)
        return 0;

    size = fattrs.st_size;

    src = (char *) malloc(sizeof(char) * (size + 1));
    fread(src, sizeof(char), size, f);
    src[size] = '\0';

    printf("done!\n");
    printf("\n");

	printf("%s", CGRN);
	printf("%s\n", path);
	printf("%s", CDFT);

	printf("%s", CLYEL);
	printf("%s\n", src);
	printf("%s", CDFT);

    // compiling
    s_id = glCreateShader(GL_VERTEX_SHADER);
    if (!s_id)
        return 0;

    glShaderSource(s_id, 1, &src, NULL);

    printf("Compiling... ");

    glCompileShader(s_id);

    glGetShaderiv(s_id, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(s_id, 512, NULL, log);

		printf("%s", CRED);
        printf("failed!\n");
		printf("%s", CDFT);

        printf("Vertex shader log: %s\n", log);

        return 0;
    }

	printf("done.\n");

    fclose(f);
    free(src);

    return s_id;
}

GLuint
Shader::createFragmentShader (const char * path)
{
    FILE * f;
    struct stat fattrs;
    size_t size;
    GLchar * src;
    GLchar * log = NULL;
    GLint status;
    GLuint s_id;

    // reading
    printf("\nReading \"%s\" (fragment shader)... ", path);

    f = fopen(path, "r");
    if (!f) {
		printf("%s", CRED);
        printf("failed!\n");
		printf("%s", CDFT);

        return 0;
    }

    // get size of the file
    if (stat(path, &fattrs) < 0)
        return 0;

    size = fattrs.st_size;

    src = (char *) malloc(sizeof(char) * (size + 1));
    fread(src, sizeof(char), size, f);
    src[size] = '\0';

    printf("done!\n");
    printf("\n");

	printf("%s", CGRN);
	printf("%s\n", path);
	printf("%s", CDFT);

	printf("%s", CLYEL);
	printf("%s\n", src);
	printf("%s", CDFT);

    // compiling
    s_id = glCreateShader(GL_FRAGMENT_SHADER);
    if (!s_id)
        return 0;

    glShaderSource(s_id, 1, &src, NULL);

    printf("Compiling... ");

    glCompileShader(s_id);

    glGetShaderiv(s_id, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(s_id, 512, NULL, log);

		printf("%s", CRED);
        printf("failed!\n");
		printf("%s", CDFT);

        printf("Fragment shader log: %s\n", log);

        return 0;
    }

	printf("done.\n");

    fclose(f);
    free(src);

    return s_id;
}

GLuint
Shader::createShaderProgram (GLuint vs_id, GLuint fs_id)
{
    GLint status;
    GLchar * log = NULL;

    this->id = glCreateProgram();

    glAttachShader(this->id, vs_id);
    glAttachShader(this->id, fs_id);

    printf("Creating shader program... ");

    glLinkProgram(this->id);

    glGetProgramiv(this->id, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(this->id, 512, NULL, log);

		printf("%s", CRED);
        printf("failed!\n");
		printf("%s", CDFT);

        printf("Shader program log: %s\n", log);

        return 0;
    }

    printf("done.\n");

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    return this->id;
}

void
Shader::use ()
{
    glUseProgram(id);
}

GLuint
Shader::getId ()
{
    return id;
}

template <typename T>
void
Shader::setValue (const char * name, T &value)
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void
Shader::setVec3 (const char * name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void
Shader::setMat4 (const char * name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE,
        &mat[0][0]);
}
