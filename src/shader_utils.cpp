#include <shader_utils.h>

GLuint
ShaderCreate(const char *vertex_shader_path, const char *fragment_shader_path) {
	int success;
	char log[512];
	int i;

	/* vertex shader */
	printf("Reading vertex shader file \"%s\"... ", vertex_shader_path);
	/*std::string vertex_shader_source;
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
	}*/

	FILE *vertex_shader_file = fopen(vertex_shader_path, "r");
	char *vertex_shader_source = (char *) malloc(sizeof(char));
	const char *vertex_shader_source_pointer;
	i = 0;
	while (1) {
		char c = fgetc(vertex_shader_file);

		if (c == EOF) {
			vertex_shader_source_pointer = vertex_shader_source;
			fclose(vertex_shader_file);
			break;
		}

		vertex_shader_source = (char *) realloc(vertex_shader_source, sizeof(char) * (i + 1));
		vertex_shader_source[i] = c;
		i++;
	}

	vertex_shader_source = (char *) realloc(vertex_shader_source, sizeof(char) * (i + 1));
	vertex_shader_source[i] = '\0';

	//const char *vertex_shader_source_pointer = vertex_shader_source.c_str();
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
	printf("Reading fragment shader file \"%s\"... ", fragment_shader_path);
	/*std::string fragment_shader_source;
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
	}*/

	FILE *fragment_shader_file = fopen(fragment_shader_path, "r");
	char *fragment_shader_source = (char *) malloc(sizeof(char));
	const char *fragment_shader_source_pointer;
	i = 0;
	while (1) {
		char c = fgetc(fragment_shader_file);

		if (c == EOF) {
			fragment_shader_source_pointer = fragment_shader_source;
			fclose(fragment_shader_file);
			break;
		}

		fragment_shader_source = (char *) realloc(fragment_shader_source, sizeof(char) * (i + 1));
		fragment_shader_source[i] = c;
		i++;
	}

	fragment_shader_source = (char *) realloc(fragment_shader_source, sizeof(char) * (i + 1));
	fragment_shader_source[i] = '\0';

	//const char *fragment_shader_source_pointer = fragment_shader_source.c_str();
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
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	printf("Creating shader program... ");
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, log);
		printf("failed!\n");
		printf("Shader program log: %s\n", log);
		return 0;
	} else
		printf("done!\n");

	return program;
}
