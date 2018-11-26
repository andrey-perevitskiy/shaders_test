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
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// setup vertices
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glEnableVertexAttribArray(0);

	GLuint program = ShaderCreate("shaders/simpleshader.vert.glsl",
		"shaders/simpleshader.frag.glsl");

	// wireframe mode on
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// wireframe mode off
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window)) {
		checkInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// rotate quad
		mat4 trans;
		trans = rotate(trans, (float) glfwGetTime(), vec3(0.0f, 1.0f, 1.0f));

		// enable shader
		glUseProgram(program);

		// send uniform to shader
		GLuint rotateLoc = glGetUniformLocation(program, "rotate");
		glUniformMatrix4fv(rotateLoc, 1, GL_FALSE, value_ptr(trans));

		// draw vertice by indices
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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
