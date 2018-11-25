#include <shader_utils.h>

GLuint
ShaderCreate(const char *vertex_shader_path, const char *fragment_shader_path) {
	int success;
	char log[512];

	/* vertex shader */
	printf("Reading vertex shader file... ");
	std::string vertex_shader_source;
	std::ifstream vertex_shader_file(vertex_shader_path, std::ifstream::binary);
	if (vertex_shader_file) {
		vertex_shader_file.seekg(0, vertex_shader_file.end);
		int length = vertex_shader_file.tellg();
		vertex_shader_file.seekg(0, vertex_shader_file.beg);
		char * buff = new char[length];
		vertex_shader_file.read(buff, length);
		if (vertex_shader_file)
			printf("done!\n");
		else
			printf("failed!\n");
		vertex_shader_file.close();
		vertex_shader_source = buff;
		delete[] buff;
	}

	const char *vertex_shader_source_pointer = vertex_shader_source.c_str();
	printf("\n\n\n%s\n\n\n", vertex_shader_source_pointer);
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source_pointer, NULL);
	printf("Compiling vertex shader... ");
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, log);
		printf("failed!\n");
		printf("Shader log: %s\n", log);
		return 0;
	} else
		printf("done!\n");

	/* fragment shader */
	printf("Reading fragment shader file... ");
	std::string fragment_shader_source;
	std::ifstream fragment_shader_file(fragment_shader_path, std::ifstream::binary);
	if (fragment_shader_file) {
		fragment_shader_file.seekg(0, fragment_shader_file.end);
		int length = fragment_shader_file.tellg();
		fragment_shader_file.seekg(0, fragment_shader_file.beg);
		char * buff = new char[length];
		fragment_shader_file.read(buff, length);
		if (fragment_shader_file)
			printf("done!\n");
		else
			printf("failed!\n");
		fragment_shader_file.close();
		fragment_shader_source = buff;
		delete[] buff;
	}

	const char *fragment_shader_source_pointer = fragment_shader_source.c_str();
	printf("\n\n\n%s\n\n\n", fragment_shader_source_pointer);
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source_pointer, NULL);
  printf("Compiling fragment shader... ");
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, log);
		printf("failed!\n");
		printf("Shader log: %s\n", log);
		return 0;
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
		return 0;
	} else
		printf("done!\n");

	return shader_program;
}
