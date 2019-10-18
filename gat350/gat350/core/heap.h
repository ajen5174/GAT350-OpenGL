#pragma once

class heap
{
public:
	struct alloc_header
	{
		size_t signature;
		size_t size;
		alloc_header* next;
		alloc_header* prev;
	};

public:
	heap() {}
	~heap();

	void* allocate(size_t size);
	void free(void* ptr);

	void report();

private:
	void free(alloc_header* header);

private:
	size_t m_allocated = 0;
	size_t m_allocated_total = 0;
	size_t m_allocated_peak = 0;
	size_t m_allocations = 0;
	size_t m_allocations_total = 0;

	alloc_header* m_alloc_head = nullptr;
};