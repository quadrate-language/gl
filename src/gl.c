#include <glad/glad.h>
#include <qdrt/ffi.h>
#include <qdrt/runtime.h>
#include <qdrt/stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// Initialization
// ============================================================================

// LoadGL( -- success:i64 )
// Must be called after creating an OpenGL context
int LoadGL(qd_context* ctx) {
	int success = gladLoadGL();
	qd_push_i(ctx, success ? 1 : 0);
	return 0;
}

// GetVersion( -- major:i64 minor:i64 )
int GetVersion(qd_context* ctx) {
	qd_push_i(ctx, GLVersion.major);
	qd_push_i(ctx, GLVersion.minor);
	return 0;
}

// ============================================================================
// State Management
// ============================================================================

// Enable( cap:i64 -- )
int Enable(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in Enable: Stack underflow\n");
		abort();
	}
	qd_stack_element_t cap_elem;
	qd_stack_pop(ctx->st, &cap_elem);
	if (cap_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in Enable: Type error\n");
		abort();
	}
	glEnable((GLenum)cap_elem.value.i);
	return 0;
}

// Disable( cap:i64 -- )
int Disable(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in Disable: Stack underflow\n");
		abort();
	}
	qd_stack_element_t cap_elem;
	qd_stack_pop(ctx->st, &cap_elem);
	if (cap_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in Disable: Type error\n");
		abort();
	}
	glDisable((GLenum)cap_elem.value.i);
	return 0;
}

// ClearColor( r:f64 g:f64 b:f64 a:f64 -- )
int ClearColor(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 4) {
		fprintf(stderr, "Fatal error in ClearColor: Stack underflow\n");
		abort();
	}
	qd_stack_element_t a_elem, b_elem, g_elem, r_elem;
	qd_stack_pop(ctx->st, &a_elem);
	qd_stack_pop(ctx->st, &b_elem);
	qd_stack_pop(ctx->st, &g_elem);
	qd_stack_pop(ctx->st, &r_elem);
	if (r_elem.type != QD_STACK_TYPE_FLOAT || g_elem.type != QD_STACK_TYPE_FLOAT ||
			b_elem.type != QD_STACK_TYPE_FLOAT || a_elem.type != QD_STACK_TYPE_FLOAT) {
		fprintf(stderr, "Fatal error in ClearColor: Type error\n");
		abort();
	}
	glClearColor((GLfloat)r_elem.value.f, (GLfloat)g_elem.value.f, (GLfloat)b_elem.value.f,
			(GLfloat)a_elem.value.f);
	return 0;
}

// Clear( mask:i64 -- )
int Clear(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in Clear: Stack underflow\n");
		abort();
	}
	qd_stack_element_t mask_elem;
	qd_stack_pop(ctx->st, &mask_elem);
	if (mask_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in Clear: Type error\n");
		abort();
	}
	glClear((GLbitfield)mask_elem.value.i);
	return 0;
}

// Viewport( x:i64 y:i64 width:i64 height:i64 -- )
int Viewport(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 4) {
		fprintf(stderr, "Fatal error in Viewport: Stack underflow\n");
		abort();
	}
	qd_stack_element_t height_elem, width_elem, y_elem, x_elem;
	qd_stack_pop(ctx->st, &height_elem);
	qd_stack_pop(ctx->st, &width_elem);
	qd_stack_pop(ctx->st, &y_elem);
	qd_stack_pop(ctx->st, &x_elem);
	if (x_elem.type != QD_STACK_TYPE_INT || y_elem.type != QD_STACK_TYPE_INT ||
			width_elem.type != QD_STACK_TYPE_INT || height_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in Viewport: Type error\n");
		abort();
	}
	glViewport((GLint)x_elem.value.i, (GLint)y_elem.value.i, (GLsizei)width_elem.value.i,
			(GLsizei)height_elem.value.i);
	return 0;
}

// ============================================================================
// Buffer Objects
// ============================================================================

// GenBuffer( -- buffer:i64 )
int GenBuffer(qd_context* ctx) {
	GLuint buffer;
	glGenBuffers(1, &buffer);
	qd_push_i(ctx, (int64_t)buffer);
	return 0;
}

// DeleteBuffer( buffer:i64 -- )
int DeleteBuffer(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in DeleteBuffer: Stack underflow\n");
		abort();
	}
	qd_stack_element_t buffer_elem;
	qd_stack_pop(ctx->st, &buffer_elem);
	if (buffer_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in DeleteBuffer: Type error\n");
		abort();
	}
	GLuint buffer = (GLuint)buffer_elem.value.i;
	glDeleteBuffers(1, &buffer);
	return 0;
}

// BindBuffer( target:i64 buffer:i64 -- )
int BindBuffer(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 2) {
		fprintf(stderr, "Fatal error in BindBuffer: Stack underflow\n");
		abort();
	}
	qd_stack_element_t buffer_elem, target_elem;
	qd_stack_pop(ctx->st, &buffer_elem);
	qd_stack_pop(ctx->st, &target_elem);
	if (target_elem.type != QD_STACK_TYPE_INT || buffer_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in BindBuffer: Type error\n");
		abort();
	}
	glBindBuffer((GLenum)target_elem.value.i, (GLuint)buffer_elem.value.i);
	return 0;
}

// BufferDataFloats( target:i64 data:ptr count:i64 usage:i64 -- )
int BufferDataFloats(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 4) {
		fprintf(stderr, "Fatal error in BufferDataFloats: Stack underflow\n");
		abort();
	}
	qd_stack_element_t usage_elem, count_elem, data_elem, target_elem;
	qd_stack_pop(ctx->st, &usage_elem);
	qd_stack_pop(ctx->st, &count_elem);
	qd_stack_pop(ctx->st, &data_elem);
	qd_stack_pop(ctx->st, &target_elem);
	if (target_elem.type != QD_STACK_TYPE_INT || data_elem.type != QD_STACK_TYPE_PTR ||
			count_elem.type != QD_STACK_TYPE_INT || usage_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in BufferDataFloats: Type error\n");
		abort();
	}
	glBufferData((GLenum)target_elem.value.i, (GLsizeiptr)(count_elem.value.i * sizeof(float)),
			data_elem.value.p, (GLenum)usage_elem.value.i);
	return 0;
}

// ============================================================================
// Vertex Arrays
// ============================================================================

// GenVertexArray( -- vao:i64 )
int GenVertexArray(qd_context* ctx) {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	qd_push_i(ctx, (int64_t)vao);
	return 0;
}

// DeleteVertexArray( vao:i64 -- )
int DeleteVertexArray(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in DeleteVertexArray: Stack underflow\n");
		abort();
	}
	qd_stack_element_t vao_elem;
	qd_stack_pop(ctx->st, &vao_elem);
	if (vao_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in DeleteVertexArray: Type error\n");
		abort();
	}
	GLuint vao = (GLuint)vao_elem.value.i;
	glDeleteVertexArrays(1, &vao);
	return 0;
}

// BindVertexArray( vao:i64 -- )
int BindVertexArray(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in BindVertexArray: Stack underflow\n");
		abort();
	}
	qd_stack_element_t vao_elem;
	qd_stack_pop(ctx->st, &vao_elem);
	if (vao_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in BindVertexArray: Type error\n");
		abort();
	}
	glBindVertexArray((GLuint)vao_elem.value.i);
	return 0;
}

// EnableVertexAttribArray( index:i64 -- )
int EnableVertexAttribArray(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in EnableVertexAttribArray: Stack underflow\n");
		abort();
	}
	qd_stack_element_t index_elem;
	qd_stack_pop(ctx->st, &index_elem);
	if (index_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in EnableVertexAttribArray: Type error\n");
		abort();
	}
	glEnableVertexAttribArray((GLuint)index_elem.value.i);
	return 0;
}

// VertexAttribPointer( index:i64 size:i64 type:i64 normalized:i64 stride:i64 offset:i64 -- )
int VertexAttribPointer(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 6) {
		fprintf(stderr, "Fatal error in VertexAttribPointer: Stack underflow\n");
		abort();
	}
	qd_stack_element_t offset_elem, stride_elem, normalized_elem, type_elem, size_elem, index_elem;
	qd_stack_pop(ctx->st, &offset_elem);
	qd_stack_pop(ctx->st, &stride_elem);
	qd_stack_pop(ctx->st, &normalized_elem);
	qd_stack_pop(ctx->st, &type_elem);
	qd_stack_pop(ctx->st, &size_elem);
	qd_stack_pop(ctx->st, &index_elem);
	if (index_elem.type != QD_STACK_TYPE_INT || size_elem.type != QD_STACK_TYPE_INT ||
			type_elem.type != QD_STACK_TYPE_INT || normalized_elem.type != QD_STACK_TYPE_INT ||
			stride_elem.type != QD_STACK_TYPE_INT || offset_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in VertexAttribPointer: Type error\n");
		abort();
	}
	glVertexAttribPointer((GLuint)index_elem.value.i, (GLint)size_elem.value.i,
			(GLenum)type_elem.value.i, (GLboolean)normalized_elem.value.i, (GLsizei)stride_elem.value.i,
			(const void*)(intptr_t)offset_elem.value.i);
	return 0;
}

// ============================================================================
// Shaders
// ============================================================================

// CreateShader( type:i64 -- shader:i64 )
int CreateShader(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in CreateShader: Stack underflow\n");
		abort();
	}
	qd_stack_element_t type_elem;
	qd_stack_pop(ctx->st, &type_elem);
	if (type_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in CreateShader: Type error\n");
		abort();
	}
	GLuint shader = glCreateShader((GLenum)type_elem.value.i);
	qd_push_i(ctx, (int64_t)shader);
	return 0;
}

// DeleteShader( shader:i64 -- )
int DeleteShader(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in DeleteShader: Stack underflow\n");
		abort();
	}
	qd_stack_element_t shader_elem;
	qd_stack_pop(ctx->st, &shader_elem);
	if (shader_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in DeleteShader: Type error\n");
		abort();
	}
	glDeleteShader((GLuint)shader_elem.value.i);
	return 0;
}

// ShaderSource( shader:i64 source:str -- )
int ShaderSource(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 2) {
		fprintf(stderr, "Fatal error in ShaderSource: Stack underflow\n");
		abort();
	}
	qd_stack_element_t source_elem, shader_elem;
	qd_stack_pop(ctx->st, &source_elem);
	qd_stack_pop(ctx->st, &shader_elem);
	if (shader_elem.type != QD_STACK_TYPE_INT || source_elem.type != QD_STACK_TYPE_STR) {
		fprintf(stderr, "Fatal error in ShaderSource: Type error\n");
		abort();
	}
	const char* source = qd_string_data(source_elem.value.s);
	glShaderSource((GLuint)shader_elem.value.i, 1, &source, NULL);
	qd_string_release(source_elem.value.s);
	return 0;
}

// CompileShader( shader:i64 -- )
int CompileShader(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in CompileShader: Stack underflow\n");
		abort();
	}
	qd_stack_element_t shader_elem;
	qd_stack_pop(ctx->st, &shader_elem);
	if (shader_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in CompileShader: Type error\n");
		abort();
	}
	glCompileShader((GLuint)shader_elem.value.i);
	return 0;
}

// GetShaderCompileStatus( shader:i64 -- success:i64 )
int GetShaderCompileStatus(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in GetShaderCompileStatus: Stack underflow\n");
		abort();
	}
	qd_stack_element_t shader_elem;
	qd_stack_pop(ctx->st, &shader_elem);
	if (shader_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in GetShaderCompileStatus: Type error\n");
		abort();
	}
	GLint success;
	glGetShaderiv((GLuint)shader_elem.value.i, GL_COMPILE_STATUS, &success);
	qd_push_i(ctx, (int64_t)success);
	return 0;
}

// GetShaderInfoLog( shader:i64 -- log:str )
int GetShaderInfoLog(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in GetShaderInfoLog: Stack underflow\n");
		abort();
	}
	qd_stack_element_t shader_elem;
	qd_stack_pop(ctx->st, &shader_elem);
	if (shader_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in GetShaderInfoLog: Type error\n");
		abort();
	}
	GLint length;
	glGetShaderiv((GLuint)shader_elem.value.i, GL_INFO_LOG_LENGTH, &length);
	char* log = malloc(length + 1);
	glGetShaderInfoLog((GLuint)shader_elem.value.i, length, NULL, log);
	log[length] = '\0';
	qd_push_s(ctx, log);
	free(log);
	return 0;
}

// ============================================================================
// Programs
// ============================================================================

// CreateProgram( -- program:i64 )
int CreateProgram(qd_context* ctx) {
	GLuint program = glCreateProgram();
	qd_push_i(ctx, (int64_t)program);
	return 0;
}

// DeleteProgram( program:i64 -- )
int DeleteProgram(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in DeleteProgram: Stack underflow\n");
		abort();
	}
	qd_stack_element_t program_elem;
	qd_stack_pop(ctx->st, &program_elem);
	if (program_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in DeleteProgram: Type error\n");
		abort();
	}
	glDeleteProgram((GLuint)program_elem.value.i);
	return 0;
}

// AttachShader( program:i64 shader:i64 -- )
int AttachShader(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 2) {
		fprintf(stderr, "Fatal error in AttachShader: Stack underflow\n");
		abort();
	}
	qd_stack_element_t shader_elem, program_elem;
	qd_stack_pop(ctx->st, &shader_elem);
	qd_stack_pop(ctx->st, &program_elem);
	if (program_elem.type != QD_STACK_TYPE_INT || shader_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in AttachShader: Type error\n");
		abort();
	}
	glAttachShader((GLuint)program_elem.value.i, (GLuint)shader_elem.value.i);
	return 0;
}

// LinkProgram( program:i64 -- )
int LinkProgram(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in LinkProgram: Stack underflow\n");
		abort();
	}
	qd_stack_element_t program_elem;
	qd_stack_pop(ctx->st, &program_elem);
	if (program_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in LinkProgram: Type error\n");
		abort();
	}
	glLinkProgram((GLuint)program_elem.value.i);
	return 0;
}

// GetProgramLinkStatus( program:i64 -- success:i64 )
int GetProgramLinkStatus(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in GetProgramLinkStatus: Stack underflow\n");
		abort();
	}
	qd_stack_element_t program_elem;
	qd_stack_pop(ctx->st, &program_elem);
	if (program_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in GetProgramLinkStatus: Type error\n");
		abort();
	}
	GLint success;
	glGetProgramiv((GLuint)program_elem.value.i, GL_LINK_STATUS, &success);
	qd_push_i(ctx, (int64_t)success);
	return 0;
}

// GetProgramInfoLog( program:i64 -- log:str )
int GetProgramInfoLog(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in GetProgramInfoLog: Stack underflow\n");
		abort();
	}
	qd_stack_element_t program_elem;
	qd_stack_pop(ctx->st, &program_elem);
	if (program_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in GetProgramInfoLog: Type error\n");
		abort();
	}
	GLint length;
	glGetProgramiv((GLuint)program_elem.value.i, GL_INFO_LOG_LENGTH, &length);
	char* log = malloc(length + 1);
	glGetProgramInfoLog((GLuint)program_elem.value.i, length, NULL, log);
	log[length] = '\0';
	qd_push_s(ctx, log);
	free(log);
	return 0;
}

// UseProgram( program:i64 -- )
int UseProgram(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in UseProgram: Stack underflow\n");
		abort();
	}
	qd_stack_element_t program_elem;
	qd_stack_pop(ctx->st, &program_elem);
	if (program_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in UseProgram: Type error\n");
		abort();
	}
	glUseProgram((GLuint)program_elem.value.i);
	return 0;
}

// GetUniformLocation( program:i64 name:str -- location:i64 )
int GetUniformLocation(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 2) {
		fprintf(stderr, "Fatal error in GetUniformLocation: Stack underflow\n");
		abort();
	}
	qd_stack_element_t name_elem, program_elem;
	qd_stack_pop(ctx->st, &name_elem);
	qd_stack_pop(ctx->st, &program_elem);
	if (program_elem.type != QD_STACK_TYPE_INT || name_elem.type != QD_STACK_TYPE_STR) {
		fprintf(stderr, "Fatal error in GetUniformLocation: Type error\n");
		abort();
	}
	const char* name = qd_string_data(name_elem.value.s);
	GLint location = glGetUniformLocation((GLuint)program_elem.value.i, name);
	qd_string_release(name_elem.value.s);
	qd_push_i(ctx, (int64_t)location);
	return 0;
}

// Uniform1f( location:i64 v0:f64 -- )
int Uniform1f(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 2) {
		fprintf(stderr, "Fatal error in Uniform1f: Stack underflow\n");
		abort();
	}
	qd_stack_element_t v0_elem, location_elem;
	qd_stack_pop(ctx->st, &v0_elem);
	qd_stack_pop(ctx->st, &location_elem);
	if (location_elem.type != QD_STACK_TYPE_INT || v0_elem.type != QD_STACK_TYPE_FLOAT) {
		fprintf(stderr, "Fatal error in Uniform1f: Type error\n");
		abort();
	}
	glUniform1f((GLint)location_elem.value.i, (GLfloat)v0_elem.value.f);
	return 0;
}

// Uniform1i( location:i64 v0:i64 -- )
int Uniform1i(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 2) {
		fprintf(stderr, "Fatal error in Uniform1i: Stack underflow\n");
		abort();
	}
	qd_stack_element_t v0_elem, location_elem;
	qd_stack_pop(ctx->st, &v0_elem);
	qd_stack_pop(ctx->st, &location_elem);
	if (location_elem.type != QD_STACK_TYPE_INT || v0_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in Uniform1i: Type error\n");
		abort();
	}
	glUniform1i((GLint)location_elem.value.i, (GLint)v0_elem.value.i);
	return 0;
}

// Uniform3f( location:i64 v0:f64 v1:f64 v2:f64 -- )
int Uniform3f(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 4) {
		fprintf(stderr, "Fatal error in Uniform3f: Stack underflow\n");
		abort();
	}
	qd_stack_element_t v2_elem, v1_elem, v0_elem, location_elem;
	qd_stack_pop(ctx->st, &v2_elem);
	qd_stack_pop(ctx->st, &v1_elem);
	qd_stack_pop(ctx->st, &v0_elem);
	qd_stack_pop(ctx->st, &location_elem);
	if (location_elem.type != QD_STACK_TYPE_INT || v0_elem.type != QD_STACK_TYPE_FLOAT ||
			v1_elem.type != QD_STACK_TYPE_FLOAT || v2_elem.type != QD_STACK_TYPE_FLOAT) {
		fprintf(stderr, "Fatal error in Uniform3f: Type error\n");
		abort();
	}
	glUniform3f((GLint)location_elem.value.i, (GLfloat)v0_elem.value.f, (GLfloat)v1_elem.value.f,
			(GLfloat)v2_elem.value.f);
	return 0;
}

// Uniform4f( location:i64 v0:f64 v1:f64 v2:f64 v3:f64 -- )
int Uniform4f(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 5) {
		fprintf(stderr, "Fatal error in Uniform4f: Stack underflow\n");
		abort();
	}
	qd_stack_element_t v3_elem, v2_elem, v1_elem, v0_elem, location_elem;
	qd_stack_pop(ctx->st, &v3_elem);
	qd_stack_pop(ctx->st, &v2_elem);
	qd_stack_pop(ctx->st, &v1_elem);
	qd_stack_pop(ctx->st, &v0_elem);
	qd_stack_pop(ctx->st, &location_elem);
	if (location_elem.type != QD_STACK_TYPE_INT || v0_elem.type != QD_STACK_TYPE_FLOAT ||
			v1_elem.type != QD_STACK_TYPE_FLOAT || v2_elem.type != QD_STACK_TYPE_FLOAT ||
			v3_elem.type != QD_STACK_TYPE_FLOAT) {
		fprintf(stderr, "Fatal error in Uniform4f: Type error\n");
		abort();
	}
	glUniform4f((GLint)location_elem.value.i, (GLfloat)v0_elem.value.f, (GLfloat)v1_elem.value.f,
			(GLfloat)v2_elem.value.f, (GLfloat)v3_elem.value.f);
	return 0;
}

// ============================================================================
// Drawing
// ============================================================================

// DrawArrays( mode:i64 first:i64 count:i64 -- )
int DrawArrays(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 3) {
		fprintf(stderr, "Fatal error in DrawArrays: Stack underflow\n");
		abort();
	}
	qd_stack_element_t count_elem, first_elem, mode_elem;
	qd_stack_pop(ctx->st, &count_elem);
	qd_stack_pop(ctx->st, &first_elem);
	qd_stack_pop(ctx->st, &mode_elem);
	if (mode_elem.type != QD_STACK_TYPE_INT || first_elem.type != QD_STACK_TYPE_INT ||
			count_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in DrawArrays: Type error\n");
		abort();
	}
	glDrawArrays((GLenum)mode_elem.value.i, (GLint)first_elem.value.i, (GLsizei)count_elem.value.i);
	return 0;
}

// DrawElements( mode:i64 count:i64 type:i64 offset:i64 -- )
int DrawElements(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 4) {
		fprintf(stderr, "Fatal error in DrawElements: Stack underflow\n");
		abort();
	}
	qd_stack_element_t offset_elem, type_elem, count_elem, mode_elem;
	qd_stack_pop(ctx->st, &offset_elem);
	qd_stack_pop(ctx->st, &type_elem);
	qd_stack_pop(ctx->st, &count_elem);
	qd_stack_pop(ctx->st, &mode_elem);
	if (mode_elem.type != QD_STACK_TYPE_INT || count_elem.type != QD_STACK_TYPE_INT ||
			type_elem.type != QD_STACK_TYPE_INT || offset_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in DrawElements: Type error\n");
		abort();
	}
	glDrawElements((GLenum)mode_elem.value.i, (GLsizei)count_elem.value.i, (GLenum)type_elem.value.i,
			(const void*)(intptr_t)offset_elem.value.i);
	return 0;
}

// ============================================================================
// Textures
// ============================================================================

// GenTexture( -- texture:i64 )
int GenTexture(qd_context* ctx) {
	GLuint texture;
	glGenTextures(1, &texture);
	qd_push_i(ctx, (int64_t)texture);
	return 0;
}

// DeleteTexture( texture:i64 -- )
int DeleteTexture(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in DeleteTexture: Stack underflow\n");
		abort();
	}
	qd_stack_element_t texture_elem;
	qd_stack_pop(ctx->st, &texture_elem);
	if (texture_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in DeleteTexture: Type error\n");
		abort();
	}
	GLuint texture = (GLuint)texture_elem.value.i;
	glDeleteTextures(1, &texture);
	return 0;
}

// BindTexture( target:i64 texture:i64 -- )
int BindTexture(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 2) {
		fprintf(stderr, "Fatal error in BindTexture: Stack underflow\n");
		abort();
	}
	qd_stack_element_t texture_elem, target_elem;
	qd_stack_pop(ctx->st, &texture_elem);
	qd_stack_pop(ctx->st, &target_elem);
	if (target_elem.type != QD_STACK_TYPE_INT || texture_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in BindTexture: Type error\n");
		abort();
	}
	glBindTexture((GLenum)target_elem.value.i, (GLuint)texture_elem.value.i);
	return 0;
}

// TexParameteri( target:i64 pname:i64 param:i64 -- )
int TexParameteri(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 3) {
		fprintf(stderr, "Fatal error in TexParameteri: Stack underflow\n");
		abort();
	}
	qd_stack_element_t param_elem, pname_elem, target_elem;
	qd_stack_pop(ctx->st, &param_elem);
	qd_stack_pop(ctx->st, &pname_elem);
	qd_stack_pop(ctx->st, &target_elem);
	if (target_elem.type != QD_STACK_TYPE_INT || pname_elem.type != QD_STACK_TYPE_INT ||
			param_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in TexParameteri: Type error\n");
		abort();
	}
	glTexParameteri((GLenum)target_elem.value.i, (GLenum)pname_elem.value.i, (GLint)param_elem.value.i);
	return 0;
}

// ActiveTexture( texture:i64 -- )
int ActiveTexture(qd_context* ctx) {
	size_t stack_size = qd_stack_size(ctx->st);
	if (stack_size < 1) {
		fprintf(stderr, "Fatal error in ActiveTexture: Stack underflow\n");
		abort();
	}
	qd_stack_element_t texture_elem;
	qd_stack_pop(ctx->st, &texture_elem);
	if (texture_elem.type != QD_STACK_TYPE_INT) {
		fprintf(stderr, "Fatal error in ActiveTexture: Type error\n");
		abort();
	}
	glActiveTexture((GLenum)texture_elem.value.i);
	return 0;
}
