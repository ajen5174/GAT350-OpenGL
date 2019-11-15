#pragma once

#include "../core/core.h"
#include <map>

template <typename TBase>
class ObjectManager
{
public:
	ObjectManager() {}

	void Add(const Name& name, std::unique_ptr<TBase> object);
	void Remove(const Name& name);

	template<typename T = TBase>
	std::shared_ptr<T> Get(const Name& name);

private:
	std::map<Name, std::shared_ptr<TBase>> m_objects;
};

template<typename TBase>
inline void ObjectManager<TBase>::Add(const Name& name, std::unique_ptr<TBase> object)
{
	auto iter = m_objects.find(name);
	if (iter == m_objects.end())
	{
		m_objects[name] = std::move(object);
	}
}

template<typename TBase>
inline void ObjectManager<TBase>::Remove(const Name& name)
{
	auto iter = m_objects.find(name);
	if (iter == m_objects.end())
	{
		m_objects.erase();
	}
}

template<typename TBase>
template<typename T>
inline std::shared_ptr<T> ObjectManager<TBase>::Get(const Name& name)
{
	std::shared_ptr<T> object;

	auto iter = m_objects.find(name);
	if (iter != m_objects.end())
	{
		object = std::static_pointer_cast<T>(iter->second);
	}
	else
	{
		object = std::make_shared<T>();
		if (object->Create(name))
		{
			m_objects[name] = object;
		}
	}

	return object;
}