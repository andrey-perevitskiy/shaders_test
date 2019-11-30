#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#include <consts.h>
#include <colors.h>
#include <shader.h>
#include <vars.h>

static void framebufferSizeCallback(GLFWwindow *window, int width,
    int height);
static void keyCallback(GLFWwindow* window, int key, int scancode,
    int action, int mods);
static void scrollCallback(GLFWwindow *window, double xoffset,
    double yoffset);

int main() {
    GLuint vao[2];
    GLuint vbo[4];
    GLuint ebo[2];

    // cube attribs
    GLfloat cube_vertices[] = {
        -0.5f, -0.5f,  0.5f, // FRONT left bottom
         0.5f, -0.5f,  0.5f, // FRONT right bottom
        -0.5f,  0.5f,  0.5f, // FRONT left top
         0.5f,  0.5f,  0.5f, // FRONT right top
        -0.5f,  0.5f, -0.5f, // BACK left top
        -0.5f, -0.5f, -0.5f, // BACK left bottom
         0.5f,  0.5f, -0.5f, // BACK right top
         0.5f, -0.5f, -0.5f  // BACK right bottom
    };

    GLfloat cube_colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f
    };

    GLuint cube_indices[] = {
        // front
        0, 1, 2,
        2, 1, 3,

        // back
        5, 7, 4,
        4, 7, 6,

        // left
        0, 2, 4,
        4, 0, 5,

        // right
        1, 3, 6,
        6, 1, 7,

        // top
        2, 3, 4,
        4, 3, 6,

        // bottom
        0, 1, 5,
        5, 1, 7
    };

    // flat attribs
    GLfloat flat_vertices[] = {
        -2.0f, -0.5f,  2.0f,
         2.0f, -0.5f,  2.0f,
        -2.0f, -0.5f, -2.0f,
         2.0f, -0.5f, -2.0f
    };

    GLfloat flat_colors[] = {
        0.5f, 0.5f, 0.5f,
    };

    GLuint flat_indices[] = {
        0, 1, 2,
        2, 1, 3,
    };

    printf("GLFW init... ");

    glewExperimental = true;
    if (!glfwInit()) {
        printf("failed!\n");

        return -1;
    }

    printf("done!\n");
    printf("Creating window... ");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(
        640,
        480,
        "Shaders test",
        NULL,
        NULL
    );
    if (window == NULL) {
        printf("failed!\n");

        glfwTerminate();

        return -1;
    }

    printf("done!\n");

    glfwSetWindowPos(window, 400, 200);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glewExperimental = true;
    glewInit();

    Shader cube_shader("shaders/cube.vert.glsl", "shaders/cube.frag.glsl");
    Shader flat_shader("shaders/flat.vert.glsl", "shaders/flat.frag.glsl");

	printf("\n");

    glGenVertexArrays(2, vao);
    glGenBuffers(4, vbo);
    glGenBuffers(2, ebo);

    // the cube
    glBindVertexArray(vao[0]);

    // setup the cube vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // vbo[0] -> cube_vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices,
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]); // ebo[0] -> cube_indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices,
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

    // setup the cube colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // vbo[1] -> cube_colors
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors,
        GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(1);

    // the flat
    glBindVertexArray(vao[1]);

    // setup the flat vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); // vbo[2] -> flat_vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(flat_vertices), flat_vertices,
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]); // ebo[1] -> flat_indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(flat_indices), flat_indices,
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

    // setup the flat colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]); // vbo[3] -> flat_colors
    glBufferData(GL_ARRAY_BUFFER, sizeof(flat_colors), flat_colors,
        GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(1);

    // wireframe mode on
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // wireframe mode off
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);

    wireframe = false;

    sc.x = 0.25f;
    sc.y = 0.25f;
    sc.z = 0.25f;

    while (!glfwWindowShouldClose(window)) {
        glm::mat4 cube_trans;
        glm::mat4 flat_trans;
        GLuint cube_trans_location;
        GLuint flat_trans_location;

        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // the cube processing
        cube_trans = glm::rotate(cube_trans, glm::radians(SCENE_ROTATE_Y),
            glm::vec3(1.0f, 0.0f, 0.0f));
        cube_trans = glm::rotate(cube_trans, SCENE_ROTATE_X,
            glm::vec3(0.0f, 1.0f, 0.0f));
        cube_trans = glm::scale(cube_trans, glm::vec3(sc.x, sc.y, sc.z));

        cube_shader.use(); // enable the cube's shader program

        // send the uniform to shader for cube rotation
        cube_trans_location = glGetUniformLocation(cube_shader.getId(),
            "cube_trans");
        glUniformMatrix4fv(cube_trans_location, 1, GL_FALSE,
            value_ptr(cube_trans));

        // draw the cube vertices by it indices
        glBindVertexArray(vao[0]);
        glDrawElements(GL_TRIANGLES, sizeof(cube_indices) /
            sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        // the flat processing
        flat_trans = glm::rotate(flat_trans, glm::radians(SCENE_ROTATE_Y),
            glm::vec3(1.0f, 0.0f, 0.0f));
        flat_trans = glm::rotate(flat_trans, SCENE_ROTATE_X,
            glm::vec3(0.0f, 1.0f, 0.0f));
        flat_trans = glm::scale(flat_trans, glm::vec3(sc.x, sc.y, sc.z));

        flat_shader.use(); // enable the flat's shader program

        // send uniform to shader for the flat rotation
        flat_trans_location = glGetUniformLocation(flat_shader.getId(),
            "flat_trans");
        glUniformMatrix4fv(flat_trans_location, 1, GL_FALSE,
            value_ptr(flat_trans));

        // draw the flat vertices by it indices
        glBindVertexArray(vao[1]);
        glDrawElements(GL_TRIANGLES, sizeof(flat_indices) /
            sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(2, vao);
    glDeleteBuffers(4, vbo);
    glDeleteBuffers(2, ebo);

    printf("Closing GLFW...\n");

    glfwTerminate();

    return 0;
}

static void
framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void
keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);

            break;
        case GLFW_KEY_F1:
            if (wireframe)
                wireframe = false;
            else
                wireframe = true;

            break;
        }
    }
}

static void
scrollCallback(GLFWwindow *window, double x_offset, double y_offset) {
    if (y_offset < 0) {
        sc.x -= SCROLL_SENSITIVITY;
        sc.y -= SCROLL_SENSITIVITY;
        sc.z -= SCROLL_SENSITIVITY;
    } else {
        sc.x += SCROLL_SENSITIVITY;
        sc.y += SCROLL_SENSITIVITY;
        sc.z += SCROLL_SENSITIVITY;
    }

    // debug
    /*printf("sc.x: %.3f | sc.y: %.3f | sc.z: %.3f\n", sc.x, sc.y, sc.z);*/

    if (sc.x <= SCROLL_SCALE_MIN || sc.y <= SCROLL_SCALE_MIN ||
            sc.z <= SCROLL_SCALE_MIN) {
        sc.x = SCROLL_SCALE_MIN;
        sc.y = SCROLL_SCALE_MIN;
        sc.z = SCROLL_SCALE_MIN;
    } else if (sc.x >= SCROLL_SCALE_MAX || sc.y >= SCROLL_SCALE_MAX ||
            sc.z >= SCROLL_SCALE_MAX) {
        sc.x = SCROLL_SCALE_MAX;
        sc.y = SCROLL_SCALE_MAX;
        sc.z = SCROLL_SCALE_MAX;
    }
}
