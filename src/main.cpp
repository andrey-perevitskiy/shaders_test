#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

	printf("Create window... ");

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

	GLfloat first_triangle[] = {
		-0.75f, -0.5f,  0.0f,
		-0.25f, -0.5f,  0.0f,
		-0.5f,   0.0f,  0.0f,
	};

	GLfloat second_triangle[] = {
		 0.75f, -0.5f,  0.0f,
		 0.25f, -0.5f,  0.0f,
		 0.5f,   0.0f,  0.0f,
	};

	GLfloat third_triangle[] = {
		-0.25f,  0.25f, 0.0f,
		 0.25f,  0.25f, 0.0f,
		 0.0f,   0.75f, 0.0f,
	};

	unsigned int VAOs[3], VBOs[3];
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);

	// setup first triangle
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glEnableVertexAttribArray(0);

	// setup second triangle
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glEnableVertexAttribArray(0);

	// setup third triangle
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(third_triangle), third_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glEnableVertexAttribArray(0);

	GLuint shader_green = ShaderCreate("shaders/green.vert.glsl",
		"shaders/green.frag.glsl");
	GLuint shader_yellow = ShaderCreate("shaders/yellow.vert.glsl",
		"shaders/yellow.frag.glsl");
	GLuint shader_cyan = ShaderCreate("shaders/cyan.vert.glsl",
		"shaders/cyan.frag.glsl");

	while (!glfwWindowShouldClose(window)) {
		checkInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw first triangle
		glUseProgram(shader_green);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw second triangle
		glUseProgram(shader_yellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw third triangle
		glUseProgram(shader_cyan);
		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwWaitEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(3, VAOs);
	glDeleteBuffers(3, VBOs);

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
