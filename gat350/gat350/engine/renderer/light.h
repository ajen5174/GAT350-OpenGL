#pragma once
#include "../framework/actor.h"
#include "model.h"

class Light : public Actor
{
public:
	enum eType
	{
		POINT,
		DIRECTION,
		SPOT
	};

public:
	OBJECT_DECLARATION(Light, Actor)
	virtual ~Light() {}

	virtual bool Create(const Name& name) override;

	void Update() override;
	void Draw(GLenum primitiveType = GL_TRIANGLES) override;

	void SetShader(class Program* shader);
	void Edit();

public:
	eType type;

	glm::vec3 ambient = glm::vec3(0.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	float cutoff;
	float exponent;
	
#ifdef _DEBUG
	std::unique_ptr<Model> m_debug_model;
#endif // _DEBUG
};