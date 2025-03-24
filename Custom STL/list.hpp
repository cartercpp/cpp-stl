#pragma once

#include "algorithms.hpp"
#include "exception.hpp"
#include "utility.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T>
		requires (default_constructible<T> && !is_const<T> && !is_volatile<T> && !is_reference<T>)
	class list
	{
	public:

		using value_type = T;
		using size_type = unsigned long long;

	private:

		struct Link
		{
			value_type m_value;
			Link* m_prev = nullptr;
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

			ForwardIterator& operator--()
			{
				CheckIfNull();
				m_link = m_link->m_prev;
				return *this;
			}

			ForwardIterator operator--(int)
			{
				const ForwardIterator temp{ *this };
				this->operator--(); //performs null check
				return temp;
			}

			ForwardIterator& operator-=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator--();

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

			friend ForwardIterator operator-(ForwardIterator iter, size_type count)
			{
				return iter -= count;
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

			ConstForwardIterator& operator--()
			{
				CheckIfNull();
				m_link = m_link->m_prev;
				return *this;
			}

			ConstForwardIterator operator--(int)
			{
				const ConstForwardIterator temp{ *this };
				this->operator--(); //performs null check
				return temp;
			}

			ConstForwardIterator& operator-=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator--();

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

			friend ConstForwardIterator operator-(ConstForwardIterator iter, size_type count)
			{
				return iter -= count;
			}

			const Link* m_link;
		};

		class ReverseIterator
		{
		public:

			using value_type = T;

			//CONSTRUCTORS & STUFF

			constexpr explicit ReverseIterator(Link* link) noexcept
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

			ReverseIterator& operator++()
			{
				CheckIfNull();
				m_link = m_link->m_prev;
				return *this;
			}

			ReverseIterator operator++(int)
			{
				const ReverseIterator temp{ *this };
				this->operator++(); //performs null check
				return temp;
			}

			ReverseIterator& operator+=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator++();

				return *this;
			}

			ReverseIterator& operator--()
			{
				CheckIfNull();
				m_link = m_link->m_next;
				return *this;
			}

			ReverseIterator operator--(int)
			{
				const ReverseIterator temp{ *this };
				this->operator--(); //performs null check
				return temp;
			}

			ReverseIterator& operator-=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator--();

				return *this;
			}

		private:

			void CheckIfNull() const
			{
				if (!m_link)
					throw runtime_error{ "Cannot dereference an iterator that is out of bounds." };
			}

			friend constexpr bool operator==(ReverseIterator lArg, ReverseIterator rArg) noexcept
			{
				return lArg.m_link == rArg.m_link;
			}

			friend constexpr bool operator!=(ReverseIterator lArg, ReverseIterator rArg) noexcept
			{
				return lArg.m_link != rArg.m_link;
			}

			friend ReverseIterator operator+(ReverseIterator iter, size_type count)
			{
				return iter += count;
			}

			friend ReverseIterator operator+(size_type count, ReverseIterator iter)
			{
				return iter += count;
			}

			friend ReverseIterator operator-(ReverseIterator iter, size_type count)
			{
				return iter -= count;
			}

			Link* m_link;
		};

		class ConstReverseIterator
		{
		public:

			using value_type = const T;

			//CONSTRUCTORS & STUFF

			constexpr explicit ConstReverseIterator(const Link* link) noexcept
				: m_link(link)
			{
			}

			//METHODS & STUFF

			value_type& operator*() const
			{
				CheckIfNull();
				return m_link->m_value;
			}

			ConstReverseIterator& operator++()
			{
				CheckIfNull();
				m_link = m_link->m_prev;
				return *this;
			}

			ConstReverseIterator operator++(int)
			{
				const ConstReverseIterator temp{ *this };
				this->operator++(); //performs null check
				return temp;
			}

			ConstReverseIterator& operator+=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator++();

				return *this;
			}

			ConstReverseIterator& operator--()
			{
				CheckIfNull();
				m_link = m_link->m_next;
				return *this;
			}

			ConstReverseIterator operator--(int)
			{
				const ConstReverseIterator temp{ *this };
				this->operator--(); //performs null check
				return temp;
			}

			ConstReverseIterator& operator-=(size_type count)
			{
				for (size_type iter = 0; iter < count; ++iter)
					this->operator--();

				return *this;
			}

		private:

			void CheckIfNull() const
			{
				if (!m_link)
					throw runtime_error{ "Cannot dereference an iterator that is out of bounds." };
			}

			friend constexpr bool operator==(ConstReverseIterator lArg,
				ConstReverseIterator rArg) noexcept
			{
				return lArg.m_link == rArg.m_link;
			}

			friend constexpr bool operator!=(ConstReverseIterator lArg,
				ConstReverseIterator rArg) noexcept
			{
				return lArg.m_link != rArg.m_link;
			}

			friend ConstReverseIterator operator+(ConstReverseIterator iter, size_type count)
			{
				return iter += count;
			}

			friend ConstReverseIterator operator+(size_type count, ConstReverseIterator iter)
			{
				return iter += count;
			}

			friend ConstReverseIterator operator-(ConstReverseIterator iter, size_type count)
			{
				return iter -= count;
			}

			const Link* m_link;
		};

	public:

		using iterator = ForwardIterator;
		using const_iterator = ConstForwardIterator;
		using reverse_iterator = ReverseIterator;
		using const_reverse_iterator = ConstReverseIterator;

		//CONSTRUCTORS & STUFF

		~list()
		{
			DeallocateWithResize();
		}

		template <convertible_to<value_type>... Ts>
		list(Ts&&... args)
		{
			m_size = sizeof...(args);
			m_head = nullptr;
			m_tail = nullptr;

			if constexpr (sizeof...(args) > 0)
			{
				Link* prevLink = nullptr;
				Link* link = new Link;
				size_type index = 0;

				auto SetHeadAndTailIfNecessary = [&]() -> void {
					if (index == 0)
						m_head = link;

					if (index + 1 == m_size)
						m_tail = link;
					};

				auto AdjustLinks = [&]() -> void {
					if (prevLink)
						prevLink->m_next = link;

					link->m_prev = prevLink;
					prevLink = link;
					};

				[[maybe_unused]] const char temp[] = {
					(link->m_value = forward<Ts>(args),
						SetHeadAndTailIfNecessary(),
						AdjustLinks(),
						link->m_next = (index + 1 < m_size) ? new Link : nullptr,
						link = link->m_next,
						++index,
						'\0')...
				};
			}
		}

		list(const list<T>& other)
		{
			CopyWithResize(other);
		}

		list<T>& operator=(const list<T>& other)
		{
			CopyWithResize(other);
			return *this;
		}

		list(list<T>&& other) noexcept
		{
			m_head = other.m_head;
			m_tail = other.m_tail;
			m_size = other.m_size;

			other.m_head = other.m_tail = nullptr;
			other.m_size = 0;
		}

		list<T>& operator=(list<T>&& other) noexcept
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

		constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ m_tail };
		}

		constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ nullptr };
		}

		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ m_tail };
		}

		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ nullptr };
		}

		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ m_tail };
		}

		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ nullptr };
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

			const size_type distanceFromHead = index,
				distanceFromTail = m_size - index - 1;

			const bool iterateForwards = distanceFromHead < distanceFromTail;
			const size_type iterCount = iterateForwards ? distanceFromHead : distanceFromTail;
			Link* link = iterateForwards ? m_head : m_tail;

			for (size_type iter = 0; iter < iterCount; ++iter)
				link = iterateForwards ? link->m_next : link->m_prev;

			return link->m_value;
		}

		const value_type& operator[](size_type index) const
		{
			CheckBounds(index);

			const size_type distanceFromHead = index,
				distanceFromTail = m_size - index - 1;

			const bool iterateForwards = distanceFromHead < distanceFromTail;
			const size_type iterCount = iterateForwards ? distanceFromHead : distanceFromTail;
			const Link* link = iterateForwards ? m_head : m_tail;

			for (size_type iter = 0; iter < iterCount; ++iter)
				link = iterateForwards ? link->m_next : link->m_prev;

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
				link->m_next = m_head;

				if (m_head)
					m_head->m_prev = link;
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
				link->m_next = m_head;

				if (m_head)
					m_head->m_prev = link;
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
				link->m_prev = m_tail;

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
				link->m_prev = m_tail;

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
					link->m_next->m_prev = link;
					link = link->m_next;
				}

				++m_size;
			}

			link->m_next = nextLink;
			nextLink->m_prev = link;
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
					link->m_next->m_prev = link;
					link = link->m_next;
				}

				++m_size;
			}

			link->m_next = nextLink;
			nextLink->m_prev = link;
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
			link->m_prev = prevLink;
			link->m_next = nextLink;
			nextLink->m_prev = link;
			++m_size;
		}

		void pop_front()
		{
			CheckEmpty();
			Link* newHead = m_head->m_next;
			delete m_head;
			m_head = newHead;
			m_head->m_prev = nullptr;
			--m_size;
		}

		void pop_back()
		{
			CheckEmpty();
			Link* newTail = m_tail->m_prev;
			delete m_tail;
			m_tail = newTail;
			m_tail->m_next = nullptr;
			--m_size;
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

			if (nextLink)
				nextLink->m_prev = prevLink;
			else
				m_tail = prevLink;

			--m_size;
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

			Link* startLink = m_head;
			for (size_type index = 0; index < startIndex; ++index)
				startLink = startLink->m_next;
			Link* startLinkPrev = startLink->m_prev;

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
			{
				startLinkPrev->m_next = endLink;

				if (endLink)
					endLink->m_prev = startLinkPrev;
			}
			else
			{
				m_head = endLink;

				if (endLink)
					endLink->m_prev = nullptr;
			}

			m_size -= endIndex - startIndex;
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

		void UpdateTail()
		{
			m_tail = m_head;
			for (size_type iter = 0; iter + 1 < m_size; ++iter)
				m_tail = m_tail->m_next;
			m_tail->m_next = nullptr;
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

		void CopyWithResize(const list<T>& other)
		{
			if (this != &other)
			{
				DeallocateWithResize();

				if (!other.empty())
				{
					Link* prevLink = nullptr;
					Link* link = new Link;
					m_head = link;

					for (auto iter = other.begin(); iter != other.end(); ++iter)
					{
						link->m_value = *iter;
						link->m_prev = prevLink;
						prevLink = link;

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

		Link* m_head;
		Link* m_tail;
		size_type m_size;
	};
}