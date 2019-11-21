#pragma once
#include "object.h"
#include "../math/transform.h"

class Actor : public Object
{
public:
	OBJECT_DECLARATION(Actor, Object)
	virtual ~Actor() {}



	virtual void Update() {}
	virtual void Draw(GLenum primitiveType = GL_TRIANGLES) {}

	

	virtual void Edit()
	{ 
		Object::Edit(); 
		ImGui::Checkbox("Active", &m_active);
		m_transform.Edit(); 
	}

public:
	bool m_active = true;
	Transform m_transform;
	class Scene* m_scene = nullptr;
};