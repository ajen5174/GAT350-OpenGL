#include "math.h"

float math::magnitude(const glm::vec3& v)
{
	

	return sqrt(dot(v, v));
}

float math::distance(const glm::vec3& v1, const glm::vec3& v2)
{
	return magnitude(v1 - v2);
}

float math::dot(const glm::vec3& v0, const glm::vec3& v1)
{
	return (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}

glm::vec3 math::cross(const glm::vec3& v0, const glm::vec3& v1)
{
	return glm::vec3(v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x);
}

glm::vec3 math::normalize(const glm::vec3& v)
{
	return v / magnitude(v);
}

glm::vec3 math::reflect(const glm::vec3& v, const glm::vec3& n)
{
	//not yet implemented
	return glm::vec3(0.0f);
}

glm::vec3 math::calculate_normal(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
{
	glm::vec3 vec1 = v0 - v1;
	glm::vec3 vec2 = v0 - v2;

	return normalize(cross(vec1, vec2));
}

void math::transform(std::vector<glm::vec3>& vectors, glm::mat4& matrix)
{
	for (glm::vec3& v : vectors)
	{
		v = glm::vec4(v, 1.0f) * matrix;
	}
}

void math::transform(std::vector<glm::vec3>& vectors, glm::mat3& matrix)
{
	for (glm::vec3& v : vectors)
	{
		v = v * matrix;
	}
}
