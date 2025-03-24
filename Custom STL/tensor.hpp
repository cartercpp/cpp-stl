#pragma once

#include "utility.hpp"
#include "exception.hpp"
#include "contiguous_iterator.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T, unsigned long long N, unsigned long long columns>
		requires (default_constructible<T> && copy_assignable<T> &&
			!is_const<T> && !is_volatile<T> && !is_reference<T>)
	class tensor
	{
	public:

		static_assert(N > 0, "Cannot have a 0-dimensional tensor");

		using value_type = tensor<T, N - 1, columns>;
		using size_type = unsigned long long;
		using iterator = asv::forward_iterator<tensor<T, N, columns>>;
		using const_iterator = asv::const_forward_iterator<tensor<T, N, columns>>;
		using reverse_iterator = asv::reverse_iterator<tensor<T, N, columns>>;
		using const_reverse_iterator = asv::const_reverse_iterator<tensor<T, N, columns>>;

		//CONSTRUCTORS & STUFF

		constexpr tensor() = default;

		template <convertible_to<value_type>... Ts>
		constexpr tensor(Ts&&... args)
		{
			static_assert(sizeof...(args) <= N, "Excessive # of arguments given");

			if constexpr (sizeof...(args) > 0)
			{
				size_type index = 0;

				[[maybe_unused]] const char temp[] = {
					(m_data[index] = forward<Ts>(args),
						++index,
						'\0')...
				};
			}
		}

		tensor(const tensor<T, N, columns>& other)
		{
			for (size_type index = 0; index < N; ++index)
				m_data[index] = other[index];
		}

		tensor<T, N, columns>& operator=(const tensor<T, N, columns>& other)
		{
			if (this != &other)
				for (size_type index = 0; index < N; ++index)
					m_data[index] = other[index];

			return *this;
		}

		//METHODS & STUFF

		static constexpr size_type dimensions() noexcept
		{
			return N;
		}

		static constexpr size_type size() noexcept
		{
			return columns;
		}

		constexpr iterator begin() noexcept
		{
			return iterator{ m_data };
		}

		constexpr iterator end() noexcept
		{
			return iterator{ m_data + N };
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ m_data };
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator{ m_data + N };
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ m_data };
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ m_data + N };
		}

		constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ m_data + (N - 1) };
		}

		constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ m_data - 1 };
		}

		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ m_data + (N - 1) };
		}

		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ m_data - 1 };
		}

		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ m_data + (N - 1) };
		}

		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ m_data - 1 };
		}

		value_type& operator[](size_type index)
		{
			CheckBounds(index);
			
			return m_data[index];
		}

		const value_type& operator[](size_type index) const
		{
			CheckBounds(index);

			return m_data[index];
		}

	private:

		void CheckBounds(size_type index) const
		{
			if (index >= N)
				throw out_of_range{ "Out of bounds." };
		}

		value_type m_data[N];
	};

	template <typename T, unsigned long long columns>
		requires (default_constructible<T> && copy_constructible<T>)
	class tensor<T, 1, columns>
	{
	public:

		using value_type = T;
		using size_type = unsigned long long;
		using iterator = asv::forward_iterator<tensor<T, 1, columns>>;
		using const_iterator = asv::const_forward_iterator<tensor<T, 1, columns>>;
		using reverse_iterator = asv::reverse_iterator<tensor<T, 1, columns>>;
		using const_reverse_iterator = asv::const_reverse_iterator<tensor<T, 1, columns>>;

		//CONSTRUCTORS & STUFF

		constexpr tensor() = default;

		template <convertible_to<value_type>... Ts>
		constexpr tensor(Ts&&... args)
		{
			static_assert(sizeof...(args) <= columns, "Excessive # of arguments given");

			if constexpr (sizeof...(args) > 0)
			{
				size_type index = 0;

				[[maybe_unused]] const char temp[] = {
					(m_data[index] = forward<Ts>(args),
						++index,
						'\0')...
				};
			}
		}

		tensor(const tensor<T, 1, columns>& other)
		{
			for (size_type index = 0; index < columns; ++index)
				m_data[index] = other[index];
		}

		tensor<T, 1, columns>& operator=(const tensor<T, 1, columns>& other)
		{
			if (this != &other)
				for (size_type index = 0; index < columns; ++index)
					m_data[index] = other[index];

			return *this;
		}

		//METHODS & STUFF

		static constexpr size_type dimensions() noexcept
		{
			return 1;
		}

		static constexpr size_type size() noexcept
		{
			return columns;
		}

		constexpr iterator begin() noexcept
		{
			return iterator{ m_data };
		}

		constexpr iterator end() noexcept
		{
			return iterator{ m_data + columns };
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ m_data };
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator{ m_data + columns };
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ m_data };
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ m_data + columns };
		}

		constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ m_data + (columns - 1) };
		}

		constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ m_data - 1 };
		}

		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ m_data + (columns - 1) };
		}

		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ m_data - 1 };
		}

		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ m_data + (columns - 1) };
		}

		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ m_data - 1 };
		}

		value_type& operator[](size_type index)
		{
			CheckBounds(index);

			return m_data[index];
		}

		const value_type& operator[](size_type index) const
		{
			CheckBounds(index);

			return m_data[index];
		}

	private:

		void CheckBounds(size_type index) const
		{
			if (index >= columns)
				throw out_of_range{ "Out of bounds." };
		}

		value_type m_data[columns];
	};
}