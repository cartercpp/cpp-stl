#pragma once

#include "exception.hpp"
#include "concepts.hpp"

namespace asv
{
	inline const int _maxState = 0x7fffffff;
	inline int _state = 69'420;

	constexpr void seed(int newState) noexcept
	{
		_state = newState;
	}

	template <typename numType> requires integral<numType>
	numType random(numType start, numType end)
	{
		if (start > end)
			throw invalid_argument{ "Arguments should be reversed." };

		const int rand = (_state * 1'103'515'245 + 12'345) & _maxState;
		_state = rand;
		
		return static_cast<numType>(start + (static_cast<double>(rand) / _maxState) * (end - start) + 0.5);
		//							start + random double in range [0, end - start]
		//							outputs will be in range [start, start + end - start = end]
	}

	template <typename numType> requires floating_point<numType>
	numType random(numType start, numType end)
	{
		if (start > end)
			throw invalid_argument{ "Arguments should be reversed." };

		const int rand = (_state * 1'103'515'245 + 12'345) & _maxState;
		_state = rand;

		return start + (static_cast<numType>(rand) / _maxState) * (end - start);
		//				start + random float in range [0, end - start]
		//				outputs will be in range [start, start + end - start = end]
	}
}