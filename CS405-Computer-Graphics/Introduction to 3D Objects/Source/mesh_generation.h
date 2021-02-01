#pragma once

#include <iostream>
#include <vector>
#include "GLM/glm.hpp"
#include "GLM/gtc/constants.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLAD/glad.h"

/* Generator Functions */
void GenerateParametricShapeFrom2D(
	std::vector<glm::vec3>& positions,
	std::vector<glm::vec3>& normals,
	std::vector<GLuint>& indices,
	glm::dvec2(*parametric_line)(double),
	int vertical_segments,
	int rotation_segments
);

void GenerateParametricShapeFrom3D(
	std::vector<glm::vec3>& positions,
	std::vector<glm::vec3>& normals,
	std::vector<GLuint>& indices,
	glm::dvec3(*parametric_surface)(double, double),
	int vertical_segments,
	int rotation_segments
);

/* Example 2D Parametric Functions */
glm::dvec2 ParametricHalfCircle(double);
glm::dvec2 ParametricCircle(double);
glm::dvec2 ParametricSpikes(double);