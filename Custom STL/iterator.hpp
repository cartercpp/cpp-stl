#pragma once

#include "concepts.hpp"

namespace asv
{
	template <typename IterType> requires is_one_way_iterator<IterType>
		&& requires(IterType iter, unsigned long long count) {
			{ iter += count } -> convertible_to<IterType>;
		}
	constexpr IterType next(IterType iter, unsigned long long count = 1)
	{
		return iter += count;
	}

	template <typename IterType> requires is_one_way_iterator<IterType>
	constexpr IterType next(IterType iter, unsigned long long count = 1)
	{
		for (unsigned int i = 0; i < count; ++i)
			++iter;

		return iter;
	}

	template <typename IterType> requires is_bidirectional_iterator<IterType>
		&& requires(IterType iter, unsigned long long count) {
			{ iter -= count } -> convertible_to<IterType>;
		}
	constexpr IterType prev(IterType iter, unsigned long long count = 1)
	{
		return iter -= count;
	}

	template <typename IterType> requires is_bidirectional_iterator<IterType>
	constexpr IterType prev(IterType iter, unsigned long long count = 1)
	{
		for (unsigned long long i = 0; i < count; ++i)
			--iter;

		return iter;
	}

	template <typename IterType> requires is_iterator<IterType>
		&& requires(IterType lArg, IterType rArg) {
			{ lArg < rArg } -> convertible_to<bool>;
		}
	constexpr long long distance(IterType lArg, IterType rArg)
	{
		IterType& start{ (lArg < rArg) ? lArg : rArg };
		const IterType& end{ (lArg < rArg) ? rArg : lArg };

		long long count = 0;
		while (start != end)
		{
			++count;
			++start;
		}

		return (lArg < rArg) ? count : -count;
	}
}