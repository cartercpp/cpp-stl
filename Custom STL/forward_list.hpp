#pragma once

#include "exception.hpp"
#include "utility.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T>
		requires (default_constructible<T> && !is_const<T> && !is_volatile<T> && !is_reference<T>)
	class forward_list
	{
	public:

		using value_type = T;
		using size_type = unsigned long long;

	private:

		struct Link
		{
			value_type m_value;
			Link* m_next = nullptr;
		};

		class ForwardIterator
		{
		public:

			using value_type = T;

			//CONSTRUCTORS & STUFF

			constexpr explicit ForwardIterator(Link* link) noexcept
				: m_link(link)
			{
			}

			//METHODS & STUFF

			value_type& operator*()
			{
				CheckIfNull();
				return m_link->m_value;
			}

			const value_type& operator*() const
			{
				CheckIfNull();
				return m_link->m_value;
			}

			ForwardIterator& operator++()
			{
				CheckIfNull();
				m_link = m_link->m_next;
				return *this;
			}

			ForwardIterator operator++(int)
			{
				const ForwardIterator temp{ *this };
				this->operator++(); //performs null check
				return temp;
			}

			ForwardIterator& operator+=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator++();

				return *this;
			}

		private:

			void CheckIfNull() const
			{
				if (!m_link)
					throw runtime_error{ "Cannot dereference an iterator that is out of bounds." };
			}

			friend constexpr bool operator==(ForwardIterator lArg, ForwardIterator rArg) noexcept
			{
				return lArg.m_link == rArg.m_link;
			}

			friend constexpr bool operator!=(ForwardIterator lArg, ForwardIterator rArg) noexcept
			{
				return lArg.m_link != rArg.m_link;
			}

			friend ForwardIterator operator+(ForwardIterator iter, size_type count)
			{
				return iter += count;
			}

			friend ForwardIterator operator+(size_type count, ForwardIterator iter)
			{
				return iter += count;
			}

			Link* m_link;
		};

		class ConstForwardIterator
		{
		public:

			using value_type = const T;

			//CONSTRUCTORS & STUFF

			constexpr explicit ConstForwardIterator(const Link* link) noexcept
				: m_link(link)
			{
			}

			//METHODS & STUFF

			value_type& operator*() const
			{
				CheckIfNull();
				return m_link->m_value;
			}

			ConstForwardIterator& operator++()
			{
				CheckIfNull();
				m_link = m_link->m_next;
				return *this;
			}

			ConstForwardIterator operator++(int)
			{
				const ConstForwardIterator temp{ *this };
				this->operator++(); //performs null check
				return temp;
			}

			ConstForwardIterator& operator+=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator++();

				return *this;
			}

		private:

			void CheckIfNull() const
			{
				if (!m_link)
					throw runtime_error{ "Cannot dereference an iterator that is out of bounds." };
			}

			friend constexpr bool operator==(ConstForwardIterator lArg,
				ConstForwardIterator rArg) noexcept
			{
				return lArg.m_link == rArg.m_link;
			}

			friend constexpr bool operator!=(ConstForwardIterator lArg,
				ConstForwardIterator rArg) noexcept
			{
				return lArg.m_link != rArg.m_link;
			}

			friend ConstForwardIterator operator+(ConstForwardIterator iter, size_type count)
			{
				return iter += count;
			}

			friend ConstForwardIterator operator+(size_type count, ConstForwardIterator iter)
			{
				return iter += count;
			}

			const Link* m_link;
		};

	public:

		using iterator = ForwardIterator;
		using const_iterator = ConstForwardIterator;

		//CONSTRUCTORS & STUFF

		~forward_list()
		{
			DeallocateWithResize();
		}

		template <convertible_to<value_type>... Ts>
		forward_list(Ts&&... args)
		{
			m_head = m_tail = nullptr;
			m_size = sizeof...(args);

			if constexpr (sizeof...(args) > 0)
			{
				Link* prevLink = nullptr;
				Link* link = new Link;
				m_head = link;
				size_type index = 0;

				auto SetHeadAndTailIfNecessary = [&]() -> void {
					if (index == 0)
						m_head = link;

					if (index + 1 == m_size)
						m_tail = link;
					};

				auto AdjustLinks = [&]() -> void {
					if (index + 1 < m_size)
					{
						link->m_next = new Link;
						prevLink = link;
						link = link->m_next;
					}
					};

				[[maybe_unused]] const char temp[] = {
					(link->m_value = forward<Ts>(args),
						SetHeadAndTailIfNecessary(),
						AdjustLinks(),
						++index,
						'\0')...
				};

				m_tail = link;
			}
		}

		forward_list(const forward_list<T>& other)
		{
			CopyWithResize(other);
		}

		forward_list<T>& operator=(const forward_list<T>& other)
		{
			CopyWithResize(other);
			return *this;
		}

		forward_list(forward_list<T>&& other) noexcept
			: m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
		{
			other.m_head = other.m_tail = nullptr;
			other.m_size = 0;
		}

		forward_list<T>& operator=(forward_list<T>&& other) noexcept
		{
			if (this != &other)
			{
				DeallocateWithResize();
				m_head = other.m_head;
				m_tail = other.m_tail;
				m_size = other.m_size;

				other.m_head = other.m_tail = nullptr;
				other.m_size = 0;
			}

			return *this;
		}

		//METHODS & STUFF

		constexpr iterator begin() noexcept
		{
			return iterator{ m_head };
		}

		constexpr iterator end() noexcept
		{
			return iterator{ nullptr };
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ m_head };
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator{ nullptr };
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ m_head };
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ nullptr };
		}

		constexpr size_type size() const noexcept
		{
			return m_size;
		}

		constexpr bool empty() const noexcept
		{
			return m_size == 0;
		}

		value_type& operator[](size_type index)
		{
			CheckBounds(index);

			Link* link = m_head;
			for (size_type iter = 0; iter < index; ++iter)
				link = link->m_next;

			return link->m_value;
		}

		const value_type& operator[](size_type index) const
		{
			CheckBounds(index);

			const Link* link = m_head;
			for (size_type iter = 0; iter < index; ++iter)
				link = link->m_next;

			return link->m_value;
		}

		template <typename... Ts> requires requires(Ts... args) {
			{ value_type(args...) } -> convertible_to<value_type>;
		}
		void emplace_front(Ts&&... args)
		{
			Link* link = new Link;

			try
			{
				link->m_value = value_type(forward<Ts>(args)...);

				if (m_head)
					link->m_next = m_head;
				else
					m_tail = link;

				m_head = link;
				++m_size;
			}
			catch (...)
			{
				delete link;
				throw;
			}
		}

		void push_front(const value_type& value)
		{
			Link* link = new Link;

			try
			{
				link->m_value = value;

				if (m_head)
					link->m_next = m_head;
				else
					m_tail = link;

				m_head = link;
				++m_size;
			}
			catch (...)
			{
				delete link;
				throw;
			}
		}

		template <typename... Ts> requires requires(Ts... args) {
			{ value_type(args...) } -> convertible_to<value_type>;
		}
		void emplace_back(Ts&&... args)
		{
			Link* link = new Link;

			try
			{
				link->m_value = value_type(forward<Ts>(args)...);

				if (m_tail)
					m_tail->m_next = link;
				else
					m_head = link;

				m_tail = link;
				++m_size;
			}
			catch (...)
			{
				delete link;
				throw;
			}
		}

		void push_back(const value_type& value)
		{
			Link* link = new Link;

			try
			{
				link->m_value = value;

				if (m_tail)
					m_tail->m_next = link;
				else
					m_head = link;

				m_tail = link;
				++m_size;
			}
			catch (...)
			{
				delete link;
				throw;
			}
		}

		void insert(iterator insertIter, iterator start, iterator end)
		{
			if (insertIter == this->begin())
			{
				for (iterator iter{ start }; iter != end; ++iter)
					push_front(*iter);

				return;
			}
			else if (insertIter == this->end())
			{
				for (iterator iter{ start }; iter != end; ++iter)
					push_back(*iter);

				return;
			}

			const size_type insertIndex = FindIterator(insertIter);
			//will throw if insertIter is out of bounds

			if (start == end)
				return; //strategically placed here to make sure insertIter is not out of bounds

			Link* prevLink = m_head;
			for (size_type index = 0; index + 1 < insertIndex; ++index)
				prevLink = prevLink->m_next;
			Link* nextLink = prevLink->m_next;

			prevLink->m_next = new Link;
			Link* link = prevLink->m_next;
			for (iterator iter{ start }; iter != end; ++iter)
			{
				link->m_value = *iter;

				if (iter + 1 != end)
				{
					link->m_next = new Link;
					link = link->m_next;
				}

				++m_size;
			}

			link->m_next = nextLink;
		}

		void insert(iterator insertIter, const_iterator start, const_iterator end)
		{
			if (insertIter == this->begin())
			{
				for (const_iterator iter{ start }; iter != end; ++iter)
					push_front(*iter);

				return;
			}
			else if (insertIter == this->end())
			{
				for (const_iterator iter{ start }; iter != end; ++iter)
					push_back(*iter);

				return;
			}

			const size_type insertIndex = FindIterator(insertIter);
			//will throw if insertIter is out of bounds

			if (start == end)
				return; //strategically placed here to make sure insertIter is not out of bounds

			Link* prevLink = m_head;
			for (size_type index = 0; index + 1 < insertIndex; ++index)
				prevLink = prevLink->m_next;
			Link* nextLink = prevLink->m_next;

			prevLink->m_next = new Link;
			Link* link = prevLink->m_next;
			for (const_iterator iter{ start }; iter != end; ++iter)
			{
				link->m_value = *iter;

				if (iter + 1 != end)
				{
					link->m_next = new Link;
					link = link->m_next;
				}

				++m_size;
			}

			link->m_next = nextLink;
		}

		void insert(iterator insertIter, const value_type& value)
		{
			if (insertIter == begin())
			{
				push_front(value);
				return;
			}
			else if (insertIter == end())
			{
				push_back(value);
				return;
			}

			const size_type insertIndex = FindIterator(insertIter);
			//will throw if insertIter out of bounds

			Link* prevLink = m_head;
			for (size_type iter = 0; iter + 1 < insertIndex; ++iter)
				prevLink = prevLink->m_next;
			Link* nextLink = prevLink ? prevLink->m_next : nullptr;

			Link* link = new Link;
			link->m_value = value;

			prevLink->m_next = link;
			link->m_next = nextLink;
			++m_size;
		}

		template <typename... Ts>
		void emplace(iterator insertIter, Ts&&... args)
		{
			if (insertIter == begin())
			{
				emplace_front(forward<Ts>(args)...);
				return;
			}
			else if (insertIter == end())
			{
				emplace_back(forward<Ts>(args)...);
				return;
			}

			const size_type insertIndex = FindIterator(insertIter);
			//will throw if insertIter out of bounds

			Link* prevLink = m_head;
			for (size_type iter = 0; iter + 1 < insertIndex; ++iter)
				prevLink = prevLink->m_next;
			Link* nextLink = prevLink ? prevLink->m_next : nullptr;

			Link* link = new Link;
			link->m_value = value_type(forward<Ts>(args)...);

			prevLink->m_next = link;
			link->m_next = nextLink;
			++m_size;
		}

		void erase(iterator start, iterator end)
		{
			if (empty())
				throw runtime_error{ "Container is already empty." };
			else if ((start == this->begin()) && (end == this->end()))
			{
				clear();
				return;
			}
			else if (start == end)
				return;

			const size_type startIndex = FindIterator(start),
				endIndex = FindIterator(end); //will throw if start or end are out of bounds

			if (startIndex > endIndex)
				throw invalid_argument{ "Provided range should be reversed" };

			Link* startLinkPrev = (startIndex > 0) ? m_head : nullptr;
			for (size_type index = 0; index + 1 < startIndex; ++index)
				startLinkPrev = startLinkPrev->m_next;
			Link* startLink = startLinkPrev ? startLinkPrev->m_next : m_head;

			Link* endLink = startLink;
			for (size_type index = startIndex; index < endIndex; ++index)
				endLink = endLink->m_next;

			Link* link = startLink;
			while (link != endLink)
			{
				Link* temp = link->m_next;
				delete link;
				link = temp;
			}

			if (startLinkPrev)
				startLinkPrev->m_next = endLink;
			else
				m_head = endLink;

			m_size -= endIndex - startIndex;
			UpdateTail();
		}

		void erase(iterator eraseIter)
		{
			if (empty())
				throw runtime_error{ "Container is already empty." };
			else if (eraseIter == begin())
			{
				pop_front();
				return;
			}
			else if (&*eraseIter == &m_tail->m_value)
			{
				pop_back();
				return;
			}

			const size_type eraseIndex = FindIterator(eraseIter);
			//will throw if eraseIter out of bounds
			Link* prevLink = m_head;

			for (size_type iter = 0; iter + 1 < eraseIndex; ++iter)
				prevLink = prevLink->m_next;

			Link* nextLink = prevLink->m_next ? prevLink->m_next->m_next : nullptr;
			delete prevLink->m_next;
			prevLink->m_next = nextLink;

			if (eraseIndex + 1 == m_size)
				UpdateTail();

			--m_size;
		}

		void pop_front()
		{
			CheckEmpty();
			Link* newHead = m_head->m_next;
			delete m_head;
			m_head = newHead;
			--m_size;
		}

		void pop_back()
		{
			CheckEmpty();
			delete m_tail;
			m_tail = nullptr;
			--m_size;
			UpdateTail();
		}

		void clear()
		{
			DeallocateWithResize();
		}

	private:

		void CheckBounds(size_type index) const
		{
			if (index >= m_size)
				throw out_of_range{ "Out of bounds." };
		}

		void CheckEmpty() const
		{
			if (m_size == 0)
				throw runtime_error{ "Container is already empty." };
		}

		//not a const member function b/c no const_iterator
		size_type FindIterator(iterator searchIter)
		{
			if (searchIter == end())
				return m_size;

			size_type index = 0;
			for (iterator iter{ begin() }; iter != end(); ++iter)
			{
				if (iter == searchIter)
					return index;

				++index;
			}

			throw invalid_argument{ "Iterator is out of bounds." };
		}

		void DeallocateWithResize()
		{
			while (m_head) //intentional: iterate by m_head instead of by m_size
			{
				Link* nextLink = m_head->m_next;
				delete m_head;
				m_head = nextLink;
			}

			m_head = m_tail = nullptr;
			m_size = 0;
		}

		void CopyWithResize(const forward_list<T>& other)
		{
			if (this != &other)
			{
				DeallocateWithResize();

				if (!other.empty())
				{
					Link* link = new Link;
					m_head = link;

					for (auto iter = other.begin(); iter != other.end(); ++iter)
					{
						link->m_value = *iter;

						if ((iter + 1) != other.end())
						{
							link->m_next = new Link;
							link = link->m_next;
						}
					}

					m_tail = link;
				}

				m_size = other.size();
			}
		}

		void UpdateTail()
		{
			m_tail = m_head;
			for (size_type iter = 0; iter + 1 < m_size; ++iter)
				m_tail = m_tail->m_next;
			m_tail->m_next = nullptr;
		}

		Link* m_head;
		Link* m_tail;
		size_type m_size;
	};
}