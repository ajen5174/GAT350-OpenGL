#include "heap.h"
#include "assert.h"
#include "types.h"

#include <new>
#include <iostream>

#define MEMORY_SIGNATURE 0xDEADC0DE

heap::~heap()
{
	report();
	//ASSERT_MSG(m_allocations == 0, "memory leak.");
}

void* heap::allocate(size_t size)
{
	size_t total_size = size + sizeof(alloc_header);
	u8* memory = static_cast<u8*>(malloc(total_size));
	alloc_header* header = (alloc_header*)(memory);
	header->size = size;
	header->signature = MEMORY_SIGNATURE;
	header->next = m_alloc_head;
	header->prev = nullptr;

	if (m_alloc_head != nullptr)
	{
		m_alloc_head->prev = header;
	}
	m_alloc_head = header;

	m_allocated += size;
	m_allocated_total += size;
	if (m_allocated > m_allocated_peak) m_allocated_peak = m_allocated;
	m_allocations++;
	m_allocations_total++;

	void* ptr = memory + sizeof(alloc_header);

	return ptr;
}

void heap::free(void* ptr)
{
	alloc_header* header = (alloc_header*)((u8*)ptr - sizeof(alloc_header));
	ASSERT(header->signature == MEMORY_SIGNATURE);

	free(header);
}

void heap::report()
{
	std::cout << "allocated (bytes): " << m_allocated << std::endl;
	std::cout << "allocated total (bytes): " << m_allocated_total << std::endl;
	std::cout << "allocated peak (bytes): " << m_allocated_peak << std::endl;

	std::cout << "allocations: " << m_allocations << std::endl;
	std::cout << "allocations total: " << m_allocations_total << std::endl;
	
	alloc_header* header = m_alloc_head;
	while (header)
	{
		std::cout << header->size << std::endl;
		header = header->next;
	}
}

void heap::free(alloc_header* header)
{
	if (header->prev == nullptr)
	{
		ASSERT(header == m_alloc_head);
		m_alloc_head = header->next;
	}
	else
	{
		header->prev->next = header->next;
	}

	if (header->next != nullptr)
	{
		header->next->prev = header->prev;
	}

	m_allocated -= header->size;
	m_allocations--;

	::free(header);
}
