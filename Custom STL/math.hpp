#pragma once

#include "exception.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename numType> requires number<numType>
	constexpr numType abs(numType num) noexcept
	{
		return (num > 0) ? num : (0 - num);
	}

	template <typename numType> requires number<numType>
	constexpr numType abs_difference(numType lArg, numType rArg) noexcept
	{
		return (lArg > rArg) ? (lArg - rArg) : (rArg - lArg);
	}

	template <typename numType> requires floating_point<numType>
	constexpr numType sqrt(numType num)
	{
		if (num < 0)
			throw invalid_argument{ "Cannot compute the square root of a negative number" };
		else if (num == 0)
			return 0;

		numType x = num / 2;
		numType prev = 0;

		while (abs_difference(x, prev) > 0.0001) // Iterate until convergence
		{
			prev = x;
			x = (x + num / x) / 2;
		}

		return x;
	}
}