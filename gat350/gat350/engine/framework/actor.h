#pragma once
#include "object.h"
#include "../math/transform.h"

class Actor : public Object
{
public:
	OBJECT_DECLARATION(Actor, Object)

	virtual ~Actor() {}

	Transform& GetTransform() { return m_transform; }

	virtual void Edit()
	{ 
		Object::Edit(); 
		m_transform.Edit(); 
	}

protected:
	Transform m_transform;
};