#pragma once

#include "iterator.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T> requires movable<T>
	constexpr void swap(T& lArg, T& rArg)
	{
		T temp{ move(lArg) };
		lArg = move(rArg);
		rArg = move(temp);
	}

	template <typename IterType>
	concept valid_iter_for_algorithms = is_one_way_iterator<IterType> && !is_const<IterType>
		&& !is_volatile<IterType> && !is_reference<IterType>;

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& requires(Pred pred, typename IterType::value_type value) {
			{ pred(value) };
		}
	constexpr void for_each(IterType start, IterType end, Pred pred)
	{
		for (IterType iter{ start }; iter != end; ++iter)
			pred(*iter);
	}

	template <typename IterType> requires valid_iter_for_algorithms<IterType>
		&& requires(typename IterType::value_type lArg, typename IterType::value_type rArg) {
			{ lArg != rArg } -> convertible_to<bool>;
			{ lArg == rArg } -> convertible_to<bool>;
		}
	constexpr IterType find(IterType start, IterType end, const typename IterType::value_type& value)
	{
		for (IterType iter{ start }; iter != end; ++iter)
			if (*iter == value)
				return iter;

		return end;
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& requires(Pred pred, typename IterType::value_type value) {
			{ pred(value) } -> convertible_to<bool>;
		}
	constexpr IterType find_if(IterType start, IterType end, Pred pred)
	{
		for (IterType iter{ start }; iter != end; ++iter)
			if (pred(*iter))
				return iter;

		return end;
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& requires(Pred pred, typename IterType::value_type value) {
			{ pred(value) } -> convertible_to<bool>;
		}
	constexpr IterType find_if_not(IterType start, IterType end, Pred pred)
	{
		for (IterType iter{ start }; iter != end; ++iter)
			if (!pred(*iter))
				return iter;

		return end;
	}

	template <typename IterType> requires valid_iter_for_algorithms<IterType>
		&& requires(typename IterType::value_type lArg, typename IterType::value_type rArg) {
			{ lArg == rArg } -> convertible_to<bool>;
		}
	constexpr unsigned long long count(IterType start, IterType end,
		const typename IterType::value_type& value)
	{
		unsigned long long count = 0;

		for (IterType iter{ start }; iter != end; ++iter)
			if (*iter == value)
				++count;

		return count;
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& requires(Pred pred, typename IterType::value_type value) {
			{ pred(value) } -> convertible_to<bool>;
		}
	constexpr unsigned long long count_if(IterType start, IterType end, Pred pred)
	{
		unsigned long long count = 0;

		for (IterType iter{ start }; iter != end; ++iter)
			if (pred(*iter))
				++count;

		return count;
	}

	template <typename IterType> requires valid_iter_for_algorithms<IterType>
		&& requires(typename IterType::value_type A, typename IterType::value_type B) {
			{ A += B } -> convertible_to<typename IterType::value_type>;
		} && default_constructible<typename IterType::value_type>
	constexpr typename IterType::value_type accumulate(IterType start, IterType end,
		typename IterType::value_type value = {})
	{
		for (IterType iter{ start }; iter != end; ++iter)
			value += *iter;

		return value;
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& copyable<IterType> && copyable<typename IterType::value_type>
		&& requires (Pred pred, typename IterType::value_type lArg,
			typename IterType::value_type rArg)
		{
			{ pred(lArg, rArg) } -> convertible_to<bool>;
		}
	constexpr void sort(IterType start, IterType end, Pred pred)
	{
		IterType iter{ start };

		if (start != end)
			while (true)
			{
				IterType prevIter{ iter };
				++iter;

				if (iter == end)
					break;
				else if (!pred(*prevIter, *iter))
				{
					if constexpr (movable<typename IterType::value_type>)
						swap(*prevIter, *iter);
					else
					{
						typename IterType::value_type tempValue{ *prevIter };
						*prevIter = *iter;
						*iter = tempValue;
					}

					iter = start; //IterType may not be bidirectional :|
				}
			}
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& copy_constructible<IterType>
		&& requires (Pred pred, typename IterType::value_type lArg,
			typename IterType::value_type rArg)
			{
				{ pred(lArg, rArg) } -> convertible_to<bool>;
			}
	constexpr bool is_sorted(IterType start, IterType end, Pred pred)
	{
		IterType iter{ start };

		if (start != end)
			while (true)
			{
				const IterType prevIter{ iter };
				++iter;

				if (iter == end)
					break;
				else if (!pred(*prevIter, *iter))
					return false;
			}

		return true;
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& copy_constructible<IterType>
		&& requires (Pred pred, typename IterType::value_type arg)
		{
			{ pred(arg) } -> convertible_to<bool>;
		}
	constexpr bool all_of(IterType start, IterType end, Pred pred)
	{
		for (IterType iter{ start }; iter != end; ++iter)
			if (!pred(*iter))
				return false;

		return true;
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& copy_constructible<IterType>
		&& requires (Pred pred, typename IterType::value_type arg)
		{
			{ pred(arg) } -> convertible_to<bool>;
		}
	constexpr bool any_of(IterType start, IterType end, Pred pred)
	{
		for (IterType iter{ start }; iter != end; ++iter)
			if (pred(*iter))
				return true;

		return false;
	}

	template <typename IterType, typename Pred> requires valid_iter_for_algorithms<IterType>
		&& copy_constructible<IterType>
		&& requires (Pred pred, typename IterType::value_type arg)
		{
			{ pred(arg) } -> convertible_to<bool>;
		}
	constexpr bool none_of(IterType start, IterType end, Pred pred)
	{
		for (IterType iter{ start }; iter != end; ++iter)
			if (pred(*iter))
				return false;

		return true;
	}

	template <typename IterType> requires valid_iter_for_algorithms<IterType>
		&& copyable<IterType>
		&& requires(typename IterType::value_type lArg, typename IterType::value_type rArg) {
			{ lArg > rArg } -> convertible_to<bool>;
		}
	constexpr IterType max(IterType start, IterType end)
	{
		IterType output{ start };

		for (IterType iter = next(start); iter != end; ++iter)
			if (*iter > *output)
				output = iter;

		return output;
	}

	template <typename IterType> requires valid_iter_for_algorithms<IterType>
		&& copyable<IterType>
		&& requires(typename IterType::value_type lArg, typename IterType::value_type rArg) {
			{ lArg < rArg } -> convertible_to<bool>;
		}
	constexpr IterType min(IterType start, IterType end)
	{
		IterType output{ start };

		for (IterType iter = next(start); iter != end; ++iter)
			if (*iter < *output)
				output = iter;

		return output;
	}

	template <typename IterType> requires valid_iter_for_algorithms<IterType>
		&& copyable<IterType>
		&& requires(typename IterType::value_type lArg, typename IterType::value_type rArg) {
			{ lArg < rArg } -> convertible_to<bool>;
		}
	constexpr auto& min_element(IterType start, IterType end)
	{
		return *min(start, end);
	}

	template <typename IterType> requires valid_iter_for_algorithms<IterType>
		&& copyable<IterType>
		&& requires(typename IterType::value_type lArg, typename IterType::value_type rArg) {
			{ lArg < rArg } -> convertible_to<bool>;
		}
	constexpr auto& max_element(IterType start, IterType end)
	{
		return *max(start, end);
	}

	template <typename IterType> requires (valid_iter_for_algorithms<IterType>
		&& is_bidirectional_iterator<IterType> && movable<typename IterType::value_type>)
	constexpr void reverse(IterType start, IterType end)
	{
		while (start != end)
		{
			swap(*start, *end);
			++start;
			--end;
		}
	}
}