#include "mesh_generation.h"

/* Generator Functions */
void GenerateParametricShapeFrom2D(
	std::vector<glm::vec3>& positions,
	std::vector<glm::vec3>& normals,
	std::vector<GLuint>& indices,
	glm::dvec2(*parametric_line)(double),
	int vertical_segments,
	int rotation_segments
)
{
	auto parametric_surface = [parametric_line](double t, double r)
	{
		auto p = glm::dvec3(parametric_line(t), 0);
		return glm::rotateY(p, r * glm::two_pi<double>());
	};

	positions.reserve(vertical_segments * rotation_segments);
	for (int r = 0; r < rotation_segments; ++r)
		for (int v = 0; v < vertical_segments; ++v)
			positions.push_back(parametric_surface(v / double(vertical_segments - 1), r / double(rotation_segments)));

	normals.reserve(vertical_segments * rotation_segments);
	for (int r = 0; r < rotation_segments; ++r)
		for (int v = 0; v < vertical_segments; ++v)
		{
			auto nv = v / double(vertical_segments - 1);
			auto nr = r / double(rotation_segments);
			auto epsilonv = 1 / double(vertical_segments - 1);
			auto epsilonr = 1 / double(rotation_segments);

			auto to_next_v = parametric_surface(nv + epsilonv, nr) - parametric_surface(nv, nr);
			auto from_prev_v = parametric_surface(nv, nr) - parametric_surface(nv - epsilonv, nr);
			auto tangent_v = (to_next_v + from_prev_v) / 2.;

			auto to_next_r = parametric_surface(nv, nr + epsilonr) - parametric_surface(nv, nr);
			auto from_prev_r = parametric_surface(nv, nr) - parametric_surface(nv, nr - epsilonr);
			auto tangent_r = (to_next_r + from_prev_r) / 2.;

			auto normal = glm::normalize(glm::cross(tangent_r, tangent_v));
			normals.push_back(normal);
		}

	auto VRtoIndex = [vertical_segments, rotation_segments](int v, int r)
	{
		return (r % rotation_segments) * vertical_segments + v;
	};
	indices.reserve(rotation_segments * (vertical_segments - 1) * 6);
	for (int r = 0; r < rotation_segments; ++r)
		for (int v = 0; v < vertical_segments - 1; ++v)
		{
			indices.push_back(VRtoIndex(v + 1, r));
			indices.push_back(VRtoIndex(v, r + 1));
			indices.push_back(VRtoIndex(v, r));

			indices.push_back(VRtoIndex(v + 1, r));
			indices.push_back(VRtoIndex(v + 1, r + 1));
			indices.push_back(VRtoIndex(v, r + 1));
		}
}
 
void GenerateParametricShapeFrom3D(
	std::vector<glm::vec3>& positions,
	std::vector<glm::vec3>& normals,
	std::vector<GLuint>& indices,
	glm::dvec3(*parametric_surface)(double, double),
	int vertical_segments,
	int rotation_segments
)
{
	positions.reserve(vertical_segments * rotation_segments);
	for (int r = 0; r < rotation_segments; ++r)
		for (int v = 0; v < vertical_segments; ++v)
			positions.push_back(parametric_surface(v / double(vertical_segments - 1), r / double(rotation_segments)));

	normals.reserve(vertical_segments * rotation_segments);
	for (int r = 0; r < rotation_segments; ++r)
		for (int v = 0; v < vertical_segments; ++v)
		{
			auto nv = v / double(vertical_segments - 1);
			auto nr = r / double(rotation_segments);
			auto epsilonv = 1 / double(vertical_segments - 1);
			auto epsilonr = 1 / double(rotation_segments);

			auto to_next_v = parametric_surface(nv + epsilonv, nr) - parametric_surface(nv, nr);
			auto from_prev_v = parametric_surface(nv, nr) - parametric_surface(nv - epsilonv, nr);
			auto tangent_v = (to_next_v + from_prev_v) / 2.;

			auto to_next_r = parametric_surface(nv, nr + epsilonr) - parametric_surface(nv, nr);
			auto from_prev_r = parametric_surface(nv, nr) - parametric_surface(nv, nr - epsilonr);
			auto tangent_r = (to_next_r + from_prev_r) / 2.;

			auto normal = glm::normalize(glm::cross(tangent_r, tangent_v));
			normals.push_back(normal);
		}

	auto VRtoIndex = [vertical_segments, rotation_segments](int v, int r)
	{
		return (r % rotation_segments) * vertical_segments + v;
	};
	indices.reserve(rotation_segments * (vertical_segments - 1) * 6);
	for (int r = 0; r < rotation_segments; ++r)
		for (int v = 0; v < vertical_segments - 1; ++v)
		{
			indices.push_back(VRtoIndex(v + 1, r));
			indices.push_back(VRtoIndex(v, r + 1));
			indices.push_back(VRtoIndex(v, r));

			indices.push_back(VRtoIndex(v + 1, r));
			indices.push_back(VRtoIndex(v + 1, r + 1));
			indices.push_back(VRtoIndex(v, r + 1));
		}
}

/* Example 2D Parametric Functions */
glm::dvec2 ParametricHalfCircle(double t)
{
	// [0, 1]
	t -= 0.5;
	// [-0.5, 0.5]
	t *= glm::pi<double>();
	// [-PI*0.5, PI*0.5]
	return glm::dvec2(cos(t), sin(t));
};

glm::dvec2 ParametricCircle(double t)
{
	// [0, 1]
	t -= 0.5;
	// [-0.5, 0.5]
	t *= glm::two_pi<double>();
	// [-PI, PI]

	auto c = glm::dvec2(0.7, 0);
	auto r = 0.3;
	return glm::dvec2(cos(t), sin(t)) * r + c;
};

glm::dvec2 ParametricSpikes(double t)
{
	// [0, 1]
	t -= 0.5;
	// [-0.5, 0.5]
	t *= glm::two_pi<double>();
	// [-PI, PI]

	auto c = glm::dvec2(0.7, 0);
	auto r = 0.3;
	auto a = 2 + 4 * 2;
	return (glm::dvec2(cos(t) + sin(a*t) / a, sin(t) + cos(a*t) / a)) * r + c;
};
