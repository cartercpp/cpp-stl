#pragma once

#include "contiguous_iterator.hpp"
#include "string.hpp"

namespace asv
{
	class string_view
	{
	public:

		using value_type = const char;
		using size_type = unsigned long long;
		using iterator = asv::forward_iterator<string_view>;
		using const_iterator = asv::const_forward_iterator<string_view>;
		using reverse_iterator = asv::reverse_iterator<string_view>;
		using const_reverse_iterator = asv::const_reverse_iterator<string_view>;

		//CONSTRUCTORS & STUFF

		constexpr string_view() noexcept
			: m_str(nullptr), m_size(0)
		{
		}

		constexpr string_view(const char* str) noexcept
			: m_str(str), m_size(Strlen(str))
		{
		}

		string_view(const string& str) noexcept
			: m_str(str.data()), m_size(str.size())
		{
		}

		//METHODS & STUFF

		constexpr iterator begin() noexcept
		{
			return iterator{ m_str };
		}

		constexpr iterator end() noexcept
		{
			return iterator{ m_str ? (m_str + m_size) : m_str };
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ m_str };
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator{ m_str ? (m_str + m_size) : m_str };
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ m_str };
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ m_str ? (m_str + m_size) : m_str };
		}

		constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ (m_size > 0) ? (m_str + (m_size - 1)) : m_str };
		}

		constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ m_str ? (m_str - 1) : nullptr };
		}

		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ (m_size > 0) ? (m_str + (m_size - 1)) : m_str };
		}

		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ m_str ? (m_str - 1) : nullptr };
		}

		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ (m_size > 0) ? (m_str + (m_size - 1)) : m_str };
		}

		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ m_str ? (m_str - 1) : nullptr };
		}

		constexpr size_type size() const noexcept
		{
			return m_size;
		}

		constexpr bool empty() const noexcept
		{
			return m_size == 0;
		}

		constexpr const char* data() const noexcept
		{
			return m_str;
		}

		const char& operator[](size_type) const;

		constexpr void swap(string_view& other) noexcept
		{
			string_view temp{ *this };
			*this = other;
			other = temp;
		}

	private:

		static constexpr size_type Strlen(const char* str) noexcept
		{
			size_type length = 0;

			while (str && (*str != '\0'))
			{
				++length;
				++str;
			}

			return length;
		}

		void CheckBounds(size_type) const;

		const char* m_str;
		size_type m_size;
	};
}