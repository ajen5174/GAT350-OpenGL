#pragma once
#include "../framework/resource.h"
#include "vertex_index_array.h"
#include "material.h"

class Mesh : public Resource
{
public:
	static const u32 ENABLE_DEPTH_TEST	= 0;
	static const u32 CULL_FRONT			= 1;
	static const u32 CULL_BACK			= 2;

public:
	OBJECT_DECLARATION(Mesh, Resource)
	virtual ~Mesh() {}

	bool Create(const Name& name) override;
	void Draw(GLenum primitiveType = GL_TRIANGLES);
	void SetShader(class Program* shader);

	static bool Load(const std::string& filename, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords);

public:
	std::shared_ptr<Material> m_material;
	std::bitset<32> m_flags = (BIT(ENABLE_DEPTH_TEST) | BIT(CULL_BACK));

protected:
	VertexArray m_vertex_array;
	std::string m_directory;
};
