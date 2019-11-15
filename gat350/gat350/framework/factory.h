#pragma once
#include <string>
#include <map>

template<typename TBase>
class CreatorBase
{
public:
	virtual ~CreatorBase() {}
	virtual TBase* Create() const = 0;
};

template<typename T, typename TBase>
class Creator : public CreatorBase<TBase>
{
public:
	virtual T* Create() const 
	{ 
		return new T; 
	}
};

template<typename TBase, typename TKey = std::string>
class Factory
{
public:
	~Factory();

	template<typename T = TBase>
	std::unique_ptr<T> Create(TKey key);
	void Register(TKey key, CreatorBase<TBase>* creator);

private:
	using registry_t = std::map<TKey, std::unique_ptr<CreatorBase<TBase>>>;
	registry_t m_registry;
};

template<typename TBase, typename TKey>
inline Factory<TBase, TKey>::~Factory()
{
	m_registry.clear();
}

template<typename TBase, typename TKey>
template<typename T>
inline std::unique_ptr<T> Factory<TBase, TKey>::Create(TKey key)
{
	auto iter = m_registry.find(key);
	if (iter == m_registry.end())
	{
		return nullptr;
	}

	CreatorBase<TBase>* creator = (*iter).second.get();
	T* object = dynamic_cast<T*>(creator->Create());

	return std::unique_ptr<T>(object);
}

template<typename TBase, typename TKey>
inline void Factory<TBase, TKey>::Register(TKey key, CreatorBase<TBase>* creator)
{
	if (m_registry.find(key) == m_registry.end())
	{
		m_registry[key] = std::unique_ptr<CreatorBase<TBase>>(creator);
	}
}
