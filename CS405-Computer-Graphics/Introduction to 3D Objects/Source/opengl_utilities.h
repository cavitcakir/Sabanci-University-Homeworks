#pragma once

#include <iostream>
#include <vector>

#include "GLAD/glad.h"
#include "GLM/glm.hpp"

/* OpenGL Utility Structs */

struct VAO
{
	GLuint id;

	GLsizei vertex_count;
	GLuint position_buffer;
	GLuint normals_buffer;

	GLsizei element_array_count;
	GLuint element_array_buffer;

	VAO(
		const std::vector<glm::vec3>& positions,
		const std::vector<glm::vec3>& normals,
		const std::vector<GLuint>& indices
	);
};

/* OpenGL Utility Functions */

GLuint CreateShaderFromSource(const GLenum& shader_type, const GLchar * source);

GLuint CreateProgramFromSources(const GLchar * vertex_shader_source, const GLchar * fragment_shader_source);

