#pragma once

class ref_count
{
public:
	ref_count() {}
	ref_count(const ref_count&) = delete;
	ref_count& operator = (const ref_count&) = delete;

	void add_ref() { m_count++; }
	void release() { m_count--; }

	size_t count() { return m_count; }

private:
	size_t m_count = 0;
};