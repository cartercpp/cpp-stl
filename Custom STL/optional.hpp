#pragma once

#include "exception.hpp"
#include "utility.hpp"

namespace asv
{
	template <typename T>
	class optional
	{
	public:

		using value_type = T;

		//CONSTRUCTORS & STUFF

		~optional() noexcept
		{
			if (m_ptr)
				delete m_ptr;
		}

		constexpr optional() noexcept
			: m_ptr(nullptr)
		{
		}

		optional(const value_type& value)
			: m_ptr(new value_type(value))
		{
		}

		constexpr optional(const optional<T>& other)
			: m_ptr(other ? new value_type(*other) : nullptr)
		{
		}

		constexpr optional(optional<T>&& other) noexcept
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}

		optional<T>& operator=(const optional<T>& other)
		{
			if (this != &other)
			{
				if (other)
				{
					if (m_ptr)
						*m_ptr = *other;
					else
						m_ptr = new value_type(*other);
				}
				else if (m_ptr)
				{
					delete m_ptr;
					m_ptr = nullptr;
				}
			}

			return *this;
		}

		constexpr optional<T>& operator=(optional<T>&& other) noexcept
		{
			if (this != &other)
			{
				m_ptr = other.m_ptr;
				other.m_ptr = nullptr;
			}

			return *this;
		}

		//METHODS & STUFF

		constexpr operator bool() const noexcept
		{
			return m_ptr;
		}

		constexpr bool has_value() const noexcept
		{
			return m_ptr;
		}

		value_type& value()
		{
			CheckIfNull();
			return *m_ptr;
		}

		const value_type& value() const
		{
			CheckIfNull();
			return *m_ptr;
		}

		constexpr value_type value_or(const value_type& other) const noexcept
		{
			return m_ptr ? *m_ptr : other;
		}

		value_type& operator*()
		{
			CheckIfNull();
			return *m_ptr;
		}

		const value_type& operator*() const
		{
			CheckIfNull();
			return *m_ptr;
		}
		
		value_type* operator->()
		{
			CheckIfNull();
			return m_ptr;
		}

		const value_type* operator->() const
		{
			CheckIfNull();
			return m_ptr;
		}

		template <typename... Ts> requires requires(Ts... args) {
			{ value_type(args...) } -> convertible_to<value_type>;
		}
		constexpr void emplace(Ts&&... args)
		{
			if (m_ptr)
				*m_ptr = value_type(forward<Ts>(args)...);
			else
				m_ptr = new value_type(forward<Ts>(args)...);
		}

		constexpr void reset() noexcept
		{
			if (m_ptr)
				delete m_ptr;

			m_ptr = nullptr;
		}

		constexpr void swap(optional<T>& other) noexcept
		{
			optional<T> temp{ move(*this) };
			*this = move(other);
			other = move(temp);
		}

	private:

		void CheckIfNull() const
		{
			if (!m_ptr)
				throw runtime_error{ "Cannot dereference a nullptr" };
		}

		value_type* m_ptr;
	};
}