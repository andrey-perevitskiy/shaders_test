#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

#include <stdio.h>

#include <shader_utils.h>

static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
static void checkInput(GLFWwindow *window);

int main() {
	printf("Initialization GLFW... ");

	glewExperimental = true;
	if (!glfwInit()) {
		printf("failed!\n");
		return -1;
	} else {
		printf("done!\n");
	}

	printf("Creating window... ");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(640, 480, "Shaders test", NULL, NULL);
	if (window == NULL) {
		printf("failed!\n");
		glfwTerminate();
		return -1;
	} else
		printf("done!\n");

	glfwSetWindowPos(window, 400, 200);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glewExperimental = true;
	glewInit();

	GLfloat vertices[] = {
		-0.5f, -0.5f,  0.5f, // FRONT left bottom      (0)
		 0.5f, -0.5f,  0.5f, // FRONT right bottom     (1)
		-0.5f,  0.5f,  0.5f, // FRONT left top         (2)
		 0.5f,  0.5f,  0.5f, // FRONT right top        (3)
		-0.5f,  0.5f, -0.5f, // LEFT left top          (4)
		-0.5f, -0.5f, -0.5f, // LEFT left bottom       (5)
		 0.5f,  0.5f, -0.5f, // TOP right top          (6)
		 0.5f, -0.5f, -0.5f, // RIGHT right bottom     (7)
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
	};

	GLuint indices[] = {
		// FRONT
		0, 1, 2,
		2, 1, 3,

		// BACK
		5, 7, 4,
		4, 7, 6,

		// LEFT
		0, 2, 4,
		4, 0, 5,

		// RIGHT
		1, 3, 6,
		6, 1, 7,

		// TOP
		2, 3, 4,
		4, 3, 6,

		// BOTTOM
		0, 1, 5,
		5, 1, 7,
	};

	GLuint vao, vbo, vbo_colors, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vbo_colors);
	glGenBuffers(1, &ebo);

	// setup vertices
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

	// setup colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

	GLuint program = ShaderCreate("shaders/simpleshader.vert.glsl",
		"shaders/simpleshader.frag.glsl");

	// wireframe mode on
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// wireframe mode off
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		checkInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// rotate cube
		mat4 trans;
		trans = rotate(trans, radians(-30.0f), vec3(1.0f, 0.0f, 0.0f));
		trans = rotate(trans, (float) glfwGetTime(), vec3(0.0f, 1.0f, 0.0f));

		// enable shader
		glUseProgram(program);

		// send uniform to shader for cube rotate
		GLuint rotateLoc = glGetUniformLocation(program, "rotate");
		glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, value_ptr(trans));

		// draw vertices by indices
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	printf("Closing GLFW...\n");
	glfwTerminate();

	return 0;
}

static void
framebufferSizeCallback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void
checkInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
