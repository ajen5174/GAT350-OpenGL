#pragma once
#include "../def.h"
#include "object.h"

class System : public Object
{
public:
	OBJECT_DECLARATION(System, Object)
	virtual ~System() {}

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void Update() = 0;
};
