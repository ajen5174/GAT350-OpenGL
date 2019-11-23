#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>

#include <vector>

namespace math
{
	float magnitude(const glm::vec3& v);
	float distance(const glm::vec3& v1, const glm::vec3& v2);
	float dot(const glm::vec3& v0, const glm::vec3& v1);
	
	glm::vec3 cross(const glm::vec3& v0, const glm::vec3& v1);
	glm::vec3 normalize(const glm::vec3& v);
	glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n);

	glm::vec3 calculate_normal(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);
	glm::vec3 calculate_tangent(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec2& uv0, const glm::vec2& uv1, const glm::vec2& uv2);

	void transform(std::vector<glm::vec3>& vectors, glm::mat4& matrix);
	void transform(std::vector<glm::vec3>& vectors, glm::mat3& matrix);
}