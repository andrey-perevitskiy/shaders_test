#include <shader_utils.h>

GLuint
ShaderCreate(const char *vertex_shader_path, const char *fragment_shader_path) {
	struct stat fileattribs;
	size_t size;
	char buff[256];
	int success;

	// reading vertex shader file
#ifdef SHADER_DEBUG_PRINT_PATH
	printf("Reading vertex shader file \"%s\"... ", vertex_shader_path);
#endif

	FILE *vertex_shader_file = fopen(vertex_shader_path, "r");
	if (vertex_shader_file == NULL) {
#ifdef SHADER_DEBUG_PRINT_PATH
		printf("failed!\n");
#endif
		return 0;
	}

	// get size of file
	if (stat(vertex_shader_path, &fileattribs) < 0)
		return 0;

	size = fileattribs.st_size;

	char *vertex_shader_source = (char *) malloc(sizeof(char) * (size + 1));
	fread(vertex_shader_source, sizeof(char), size, vertex_shader_file);
	vertex_shader_source[size] = '\0';

	fclose(vertex_shader_file);
	strcpy(buff, "");

#ifdef SHADER_DEBUG_PRINT_PATH
	printf("done!\n");
#endif

#ifdef SHADER_DEBUG_PRINT_FILE
	printf("%s\n%s%s\n%s\n%s", CGRN, vertex_shader_path, CLYEL, vertex_shader_source, CDFT);
#endif

	// compiling vertex shader
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);

#ifdef SHADER_DEBUG_PRINT_COMPILE
	printf("Compiling vertex shader... ");
#endif

	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef SHADER_DEBUG_PRINT_COMPILE
		char vertex_shader_log[512];
		glGetShaderInfoLog(vertex_shader, 512, NULL, vertex_shader_log);
		printf("failed!\n");
		printf("Shader log: %s\n", vertex_shader_log);
#endif
		return 0;
	} else
#ifdef SHADER_DEBUG_PRINT_COMPILE
		printf("done!\n");
#endif

	// reading fragment shader file
#ifdef SHADER_DEBUG_PRINT_PATH
	printf("Reading fragment shader file \"%s\"... ", fragment_shader_path);
#endif

	FILE *fragment_shader_file = fopen(fragment_shader_path, "r");
	if (fragment_shader_file == NULL) {
#ifdef SHADER_DEBUG_PRINT_PATH
		printf("failed!\n");
#endif
		return 0;
	}

	// get size of file
	if (stat(vertex_shader_path, &fileattribs) < 0)
		return 0;

	size = fileattribs.st_size;

	char *fragment_shader_source = (char *) malloc(sizeof(char) * (size + 1));
	fread(fragment_shader_source, sizeof(char), size, fragment_shader_file);
	fragment_shader_source[size] = '\0';

	fclose(fragment_shader_file);

#ifdef SHADER_DEBUG_PRINT_PATH
	printf("done!\n");
#endif

#ifdef SHADER_DEBUG_PRINT_FILE
	printf("%s\n%s%s\n%s\n%s", CGRN, fragment_shader_path, CLYEL, fragment_shader_source, CDFT);
#endif

	// compiling fragment shader file
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);

#ifdef SHADER_DEBUG_PRINT_COMPILE
	printf("Compiling fragment shader... ");
#endif

	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef SHADER_DEBUG_PRINT_COMPILE
		char fragment_shader_log[512];
		glGetShaderInfoLog(fragment_shader, 512, NULL, fragment_shader_log);
		printf("failed!\n");
		printf("Shader log: %s\n", fragment_shader_log);
#endif
		return 0;
	} else
#ifdef SHADER_DEBUG_PRINT_COMPILE
		printf("done!\n");
#endif

	// creating shader program
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	// clean trash
	free(vertex_shader_source);
	free(fragment_shader_source);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

#ifdef SHADER_DEBUG
	printf("Creating shader program... ");
#endif

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
#ifdef SHADER_DEBUG
		char shader_program_log[512];
		glGetProgramInfoLog(program, 512, NULL, shader_program_log);
		printf("failed!\n");
		printf("Shader program log: %s\n", shader_program_log);
#endif
		return 0;
	} else {
#ifdef SHADER_DEBUG
		printf("done!\n");
#endif
	}

	return program;
}
