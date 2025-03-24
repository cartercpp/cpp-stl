#pragma once

#include "type_traits.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T, typename T2>
	struct pair
	{
		T first;
		T2 second;
	};

	template <typename T>
	constexpr remove_reference_t<T>&& move(T&& value) noexcept
	{
		return static_cast<remove_reference_t<T>&&>(value);
	}

	template <typename T>
	constexpr T&& forward(remove_reference_t<T>& t) noexcept
	{
		return static_cast<T&&>(t);
	}

	template <typename T>
	constexpr T&& forward(remove_reference_t<T>&& t) noexcept
	{
		static_assert(!is_lvalue_reference_v<T>, "Cannot forward an rvalue as an lvalue");
		return static_cast<T&&>(t);
	}
}