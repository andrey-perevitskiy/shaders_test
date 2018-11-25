#include <shader_utils.h>

GLuint
ShaderCreate(const char *vertex_shader_path, const char *fragment_shader_path) {
	int success;
	int i;

	/* reading vertex shader file */
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

	char *vertex_shader_source = (char *) malloc(sizeof(char));
	const char *vertex_shader_source_pointer;
	i = 0;
	while (1) {
		char c = fgetc(vertex_shader_file);
		if (c == EOF) {
#ifdef SHADER_DEBUG_PRINT_PATH
			printf("done!\n");
#endif
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

#ifdef SHADER_DEBUG_PRINT_FILE
	printf("%s\n%s\n%s", CLYEL, vertex_shader_source_pointer, CDFT);
#endif

	// compiling vertex shader
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source_pointer, NULL);

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
	} else {
#ifdef SHADER_DEBUG_PRINT_COMPILE
		printf("done!\n");
#endif
	}

	/* reading fragment shader file */
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

	char *fragment_shader_source = (char *) malloc(sizeof(char));
	const char *fragment_shader_source_pointer;
	i = 0;
	while (1) {
		char c = fgetc(fragment_shader_file);
		if (c == EOF) {
#ifdef SHADER_DEBUG_PRINT_PATH
			printf("done!\n");
#endif
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

#ifdef SHADER_DEBUG_PRINT_FILE
	printf("%s\n%s\n%s", CLYEL, fragment_shader_source_pointer, CDFT);
#endif

	// compiling fragment shader file
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source_pointer, NULL);

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
	} else {
#ifdef SHADER_DEBUG_PRINT_COMPILE
		printf("done!\n");
#endif
	}

	/* creating shader program */
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

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
