#pragma once
#include "../framework/resource.h"
#include "texture.h"
#include "program.h"

class Material : public Resource
{
public:
	OBJECT_DECLARATION(Material, Resource)
		virtual ~Material() {}

	void SetShader(Program* shader);
	void Use();

	void Edit();

public:
	glm::vec3 ambient = glm::vec3(0.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	float shininess = 100.0f;
	
	std::vector<std::shared_ptr<Texture>> textures;
};