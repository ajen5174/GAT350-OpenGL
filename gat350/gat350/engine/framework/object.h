#pragma once
#include "../def.h"
#include "../../framework/factory.h"

#define OBJECT_DECLARATION(class_name, super_class_name) \
	class_name() {} \
	class_name(const Name& name, class Engine* engine) : super_class_name(name, engine) {} \
	static const char* GetClassName() { return #class_name; } \
	static const char* GetSuperClassName() { return #super_class_name; }

class Object
{
public:
	Object() {}
	Object(const Name& name, class Engine* engine) : m_name(name), m_engine(engine) {}
	virtual ~Object() {}

	virtual bool Create(const Name& name) { m_name = name; return true; }
	 
	inline virtual void Edit() { ImGui::Text(m_name.c_str()); }

public:
	Name m_name;
	class Engine* m_engine = nullptr;
};
