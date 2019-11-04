#pragma once
#include "object.h"

class Resource : public Object
{
public:
	OBJECT_DECLARATION(Resource, Object)

	virtual ~Resource() {}
};