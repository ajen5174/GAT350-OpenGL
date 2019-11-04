#pragma once
#include "../engine.h"
#include "../framework/actor.h"

class Light : public Actor
{
public:
	OBJECT_DECLARATION(Light, Actor)
	virtual ~Light() {}

	virtual bool Create(const Name& name) { m_name = name; return true; }
	virtual void Destroy() {};

	void SetShader(class Program* program, const glm::mat4& view);
	void Edit();

public:
	//union
	//{
	//	glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//	glm::vec4 direction;
	//};

	glm::vec3 ambient = glm::vec3(0.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
};