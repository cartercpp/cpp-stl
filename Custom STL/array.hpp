#pragma once

#include "contiguous_iterator.hpp"
#include "exception.hpp"
#include "utility.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T, unsigned long long N>
		requires (default_constructible<T> && !is_const<T> && !is_volatile<T> && !is_reference<T>)
	class array
	{
	public:

		static_assert(N > 0, "An array must have a size >= 1");

		using size_type = unsigned long long;
		using value_type = T;
		using iterator = asv::forward_iterator<array<T, N>>;
		using const_iterator = asv::const_forward_iterator<array<T, N>>;
		using reverse_iterator = asv::reverse_iterator<array<T, N>>;
		using const_reverse_iterator = asv::const_reverse_iterator<array<T, N>>;

		//CONSTRUCTORS & STUFF

		array() = default;

		template <convertible_to<value_type>... Ts>
		constexpr array(Ts&&... values)
		{
			static_assert(sizeof...(values) <= N, "Excessive # of arguments given");
			size_type index = 0;
			[[maybe_unused]] const char temp[] = {
				(this->operator[](index) = forward<Ts>(values), ++index, '\0')...
			};
		}

		constexpr array(const array<T, N>& other) noexcept
		{
			for (size_type index = 0; index < N; ++index)
				this->operator[](index) = other[index];
		}

		constexpr array<T, N>& operator=(const array<T, N>& other) noexcept
		{
			for (size_type index = 0; index < N; ++index)
				this->operator[](index) = other[index];

			return *this;
		}

		//METHODS & STUFF

		static constexpr size_type size() noexcept
		{
			return N;
		}

		constexpr iterator begin() noexcept
		{
			return iterator{ &this->operator[](0) };
		}

		constexpr iterator end() noexcept
		{
			return iterator{ m_data + N + 1 };
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ &this->operator[](0) };
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator{ m_data + N + 1 };
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ &this->operator[](0) };
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ m_data + N + 1 };
		}

		constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ &this->operator[](N - 1) };
		}

		constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ m_data };
		}

		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ &this->operator[](N - 1) };
		}

		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ m_data };
		}

		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ &this->operator[](N - 1) };
		}

		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ m_data };
		}

		value_type& operator[](size_type index)
		{
			CheckBounds(index);
			return m_data[index + 1];
		}

		const value_type& operator[](size_type index) const
		{
			CheckBounds(index);
			return m_data[index + 1];
		}

	private:

		void CheckBounds(size_type index) const
		{
			if (index >= N)
				throw out_of_range{ "Out of bounds." };
		}

		value_type m_data[N + 2];
	};
}