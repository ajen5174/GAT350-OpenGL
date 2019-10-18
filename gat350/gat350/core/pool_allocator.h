#pragma once
#include <list>

template <typename T>
class PoolAllocator
{
public:
	using ptr_type = BYTE*;

public:
	PoolAllocator(size_t size);
	~PoolAllocator();

	T* Get();
	void Free(void* address);

private:
	void* m_pool = nullptr;
	std::list<void*> m_freelist;
};

template<typename T>
inline PoolAllocator<T>::PoolAllocator(size_t size)
{
	m_pool = new char[size * sizeof(T)];
	for (size_t i = 0; i < size; i++)
	{
		ptr_type current = static_cast<ptr_type>(m_pool) + (i * sizeof(T));
		m_freelist.push_back(current);
	}
}

template<typename T>
inline PoolAllocator<T>::~PoolAllocator()
{
	delete m_pool;
}

template<typename T>
inline T* PoolAllocator<T>::Get()
{
	T* element = nullptr;

	if (m_freelist.empty() == false)
	{
		element = reinterpret_cast<T*>(m_freelist.front());
		m_freelist.pop_front();
	}

	return element;
}

template<typename T>
inline void PoolAllocator<T>::Free(void* element)
{
	m_freelist.push_front(element);
}
