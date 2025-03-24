#pragma once

#include "exception.hpp"
#include "utility.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T>
		requires (default_constructible<T> && !is_const<T> && !is_volatile<T> && !is_reference<T>)
	class stack
	{
	public:

		using value_type = T;
		using size_type = unsigned long long;

		//CONSTRUCTORS & STUFF

		~stack()
		{
			DeallocateWithResize();
		}

		constexpr stack() noexcept
			: m_data(nullptr), m_size(0)
		{
		}

		template <convertible_to<T>... Ts>
		stack(Ts&&... args)
		{
			m_size = sizeof...(args);

			if constexpr (sizeof...(args) > 0)
			{
				m_data = new Link;
				Link* link = m_data;
				size_type index = 0;

				const char temp[] = {
					(link->m_value = forward<Ts>(args),
						++index,
						link->m_next = (index < m_size) ? new Link : nullptr,
						link = link->m_next,
						'\0')...
				};
			}
			else
				m_data = nullptr;
		}

		stack(const stack<T>& other)
		{
			CopyWithResize(other);
		}

		stack(stack<T>&& other) noexcept
		{
			m_data = other.m_data;
			m_size = other.m_size;

			other.m_data = nullptr;
			other.m_size = 0;
		}

		stack<T>& operator=(const stack<T>& other)
		{
			CopyWithResize(other);
			return *this;
		}

		stack<T>& operator=(stack<T>&& other) noexcept
		{
			if (this != &other)
			{
				DeallocateWithResize();
				m_data = other.m_data;
				m_size = other.m_size;
				other.m_data = nullptr;
				other.m_size = 0;
			}

			return *this;
		}

		//METHODS & STUFF

		constexpr size_type size() const noexcept
		{
			return m_size;
		}

		constexpr bool empty() const noexcept
		{
			return m_size == 0;
		}

		value_type& top()
		{
			if (m_size == 0)
				throw runtime_error{ "Container is already empty." };

			return m_data->m_value;
		}

		const value_type& top() const
		{
			if (m_size == 0)
				throw runtime_error{ "Container is already empty." };

			return m_data->m_value;
		}

		void push(const value_type& value)
		{
			Link* newHead = new Link;

			try
			{
				newHead->m_value = value;
				newHead->m_next = m_data;
				m_data = newHead;
				++m_size;
			}
			catch (...)
			{
				delete newHead;
				throw;
			}
		}

		void push(value_type&& value)
		{
			Link* newHead = new Link;

			try
			{
				newHead->m_value = move(value);
				newHead->m_next = m_data;
				m_data = newHead;
				++m_size;
			}
			catch (...)
			{
				delete newHead;
				throw;
			}
		}

		template <typename... Ts> requires requires (Ts... args) {
			{ value_type(args...) } -> convertible_to<value_type>;
		}
		void emplace(Ts&&... args)
		{
			Link* newHead = new Link;

			try
			{
				newHead->m_value = value_type(forward<Ts>(args)...);
				newHead->m_next = m_data;
				m_data = newHead;
				++m_size;
			}
			catch (...)
			{
				delete newHead;
				throw;
			}
		}

		void pop()
		{
			if (m_size == 0)
				throw runtime_error{ "Container is already empty" };

			Link* newHead = m_data->m_next;
			delete m_data;
			m_data = newHead;
			--m_size;
		}

		void clear()
		{
			DeallocateWithResize();
		}

		void swap(stack<T>& other) noexcept
		{
			stack<T> temp{ move(*this) };
			*this = move(other);
			other = move(temp);
		}

	private:

		void DeallocateWithResize()
		{
			Link* link = m_data;

			while (link)
			{
				Link* nextLink = link->m_next;
				delete link;
				link = nextLink;
			}

			m_data = nullptr;
			m_size = 0;
		}

		void CopyWithResize(const stack<T>& other)
		{
			if (this != &other)
			{
				DeallocateWithResize(); //sets m_data to nullptr and m_size to 0

				if (!other.empty())
				{
					const Link* otherLink = other.m_data;
					m_data = new Link;
					Link* link = m_data;

					for (size_type index = 0; index < other.size(); ++index)
					{
						link->m_value = otherLink->m_value;
						link->m_next = (index + 1 < other.size()) ? new Link : nullptr;
						link = link->m_next;
						otherLink = otherLink->m_next;
					}

					m_size = other.size();
				}
			}
		}

		struct Link
		{
			value_type m_value;
			Link* m_next = nullptr;
		};
		
		Link* m_data;
		size_type m_size;
	};
}