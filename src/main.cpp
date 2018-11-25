#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

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

	int success;
	char log[512];

	/* vertex shader */
	const char *vertex_shader_source =
	"#version 330 core\n"
	"layout(location = 0) in vec3 position;"
	"void main (void) {"
	"  gl_Position = vec4(position, 1.0);"
	"}";

	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	printf("Compiling vertex shader... ");
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, log);
		printf("failed!\n");
		printf("Shader log: %s\n", log);
		return -1;
	} else
		printf("done!\n");

	/* fragment shader */
	const char *fragment_shader_source =
	"#version 330 core\n"
	"out vec4 frag_color;"
	"void main (void) {"
	"  frag_color = vec4(0.0, 1.0, 0.0, 1.0);"
  "}";

  int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  printf("Compiling fragment shader... ");
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, log);
		printf("failed!\n");
		printf("Shader log: %s\n", log);
		return -1;
	} else
		printf("done!\n");

	/* shader program */
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	printf("Creating shader program... ");
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, log);
		printf("failed!\n");
		printf("Shader program log: %s\n", log);
		return -1;
	} else
		printf("done!\n");

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	while (!glfwWindowShouldClose(window)) {
		checkInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);

		// draw first triangle
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw second triangle
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw third triangle
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
