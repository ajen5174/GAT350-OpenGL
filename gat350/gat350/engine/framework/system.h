#pragma once
#include "../engine.h"

class System
{
public:
	virtual ~System() {}

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void Update() = 0;
};
