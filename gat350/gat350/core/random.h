#pragma once

#include "types.h"
#include <random>

template <typename TEngine = std::default_random_engine>
class random
{
public:
	using distribution_t = std::uniform_int_distribution<int>;
	using param_t = distribution_t::param_type;

public:
	random()
	{
		std::random_device device;
		m_engine.seed(device());
	}

	random(u32 seed)
	{
		m_engine(seed);
	}

	~random() {}

	void seed(u32 seed)
	{
		m_engine.seed(seed);
	}

	int operator() ()
	{
		param_t p{ 0,  INT_MAX };
		return m_distribution(m_engine, p);
	}

	int operator() (int max)
	{
		param_t p{ 0,  max };
		return m_distribution(m_engine, p);
	}

	int operator() (int min, int max)
	{
		param_t p{ min,  max };
		return m_distribution(m_engine, p);
	}
	
private:
	TEngine m_engine;
	distribution_t m_distribution;
};

template <typename TEngine = std::default_random_engine>
class random_real
{
public:
	using distribution_t = std::uniform_real_distribution<float>;
	using param_t = distribution_t::param_type;

public:
	random_real()
	{
		std::random_device device;
		m_engine.seed(device());
	}

	random_real(u32 seed)
	{
		m_engine(seed);
	}

	~random_real() {}

	void seed(u32 seed)
	{
		m_engine.seed(seed);
	}

	float operator() ()
	{
		param_t p{ 0.0f,  FLT_MAX };
		return m_distribution(m_engine, p);
	}

	float operator() (float max)
	{
		param_t p{ 0.0f,  max };
		return m_distribution(m_engine, p);
	}

	float operator() (float min, float max)
	{
		param_t p{ min,  max };
		return m_distribution(m_engine, p);
	}

private:
	TEngine m_engine;
	distribution_t m_distribution;
};

using random_t = random<>;
using random_real_t = random_real<>;

extern random_real_t g_random;
extern random_t g_random_int;