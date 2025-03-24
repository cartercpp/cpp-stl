#pragma once

#include "exception.hpp"
#include "utility.hpp"
#include "contiguous_iterator.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T>
		requires (default_constructible<T> && !is_const<T> && !is_volatile<T> && !is_reference<T>)
	class vector
	{
	public:

		using size_type = unsigned long long;
		using value_type = T;
		using iterator = asv::forward_iterator<vector<T>>;
		using const_iterator = asv::const_forward_iterator<vector<T>>;
		using reverse_iterator = asv::reverse_iterator<vector<T>>;
		using const_reverse_iterator = asv::const_reverse_iterator<vector<T>>;

		//CONSTRUCTORS & STUFF

		~vector()
		{
			DeallocateWithResize();
		}

		constexpr vector() noexcept
		{
			m_data = nullptr;
			m_size = m_reserved = 0;
		}

		template <convertible_to<value_type>... Ts>
		vector(Ts&&... values)
		{
			m_size = m_reserved = sizeof...(values);
			m_data = new value_type[m_reserved + 2]{ value_type{}, static_cast<value_type>(forward<Ts>(values))... };
			//									m_data[0] is for rend()
			//									m_data[m_reserved + 1] is for end()
		}

		explicit vector(iterator start, iterator end)
		{
			m_size = m_reserved = end - start;
			m_data = new T[m_reserved + 2];

			size_type index = 0;
			for (auto iter = start; iter != end; ++iter, ++index)
				this->operator[](index) = *iter;
		}

		explicit vector(const_iterator start, const_iterator end)
		{
			m_size = m_reserved = end - start;
			m_data = new T[m_reserved + 2];

			size_type index = 0;
			for (auto iter = start; iter != end; ++iter, ++index)
				this->operator[](index) = *iter;
		}

		explicit vector(reverse_iterator start, reverse_iterator end)
		{
			m_size = m_reserved = end - start;
			m_data = new T[m_reserved + 2];

			size_type index = 0;
			for (auto iter = start; iter != end; ++iter, ++index)
				this->operator[](index) = *iter;
		}

		explicit vector(const_reverse_iterator start, const_reverse_iterator end)
		{
			m_size = m_reserved = end - start;
			m_data = new T[m_reserved + 2];

			size_type index = 0;
			for (auto iter = start; iter != end; ++iter, ++index)
				this->operator[](index) = *iter;
		}

		vector(const vector<T>& other)
		{
			CopyData(other);
		}

		vector(vector<T>&& other) noexcept
			: m_data(other.m_data), m_size(other.m_size), m_reserved(other.m_reserved)
		{
			other.m_data = nullptr;
			other.m_size = other.m_reserved = 0;
		}

		vector<T>& operator=(const vector<T>& other)
		{
			CopyData(other);
			return *this;
		}

		vector<T>& operator=(vector<T>&& other) noexcept
		{
			if (this != &other)
			{
				DeallocateWithResize();
				m_data = other.m_data;
				m_size = other.m_size;
				m_reserved = other.m_reserved;
				other.m_data = nullptr;
				other.m_size = other.m_reserved = 0;
			}

			return *this;
		}

		//METHODS & STUFF

		constexpr iterator begin() noexcept
		{
			return iterator{ (m_size > 0) ? &this->operator[](0) : nullptr };
		}

		constexpr iterator end() noexcept
		{
			return iterator{ m_data ? (m_data + m_size + 1) : nullptr };
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ (m_size > 0) ? &this->operator[](0) : nullptr };
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator{ m_data ? (m_data + m_size + 1) : nullptr };
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ (m_size > 0) ? &this->operator[](0) : nullptr };
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ m_data ? (m_data + m_size + 1) : nullptr };
		}

		constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ (m_size > 0) ? &this->operator[](m_size - 1) : nullptr };
		}

		constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ m_data };
		}

		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ (m_size > 0) ? &this->operator[](m_size - 1) : nullptr };
		}

		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ m_data };
		}

		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ (m_size > 0) ? &this->operator[](m_size - 1) : nullptr };
		}

		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ m_data };
		}

		constexpr value_type* data() noexcept
		{
			return (m_size > 0) ? &this->operator[](0) : nullptr;
		}

		constexpr const value_type* data() const noexcept
		{
			return (m_size > 0) ? &this->operator[](0) : nullptr;
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

		constexpr size_type capacity() const noexcept
		{
			return m_reserved;
		}

		constexpr size_type size() const noexcept
		{
			return m_size;
		}

		constexpr bool empty() const noexcept
		{
			return m_size == 0;
		}

		void reserve(size_type newReserved)
		{
			if (newReserved > m_reserved)
			{
				T* newData = new T[newReserved + 2];
				for (size_type index = 0; index < m_size; ++index)
					newData[index + 1] = this->operator[](index);

				DeallocateWithoutResize();
				m_data = newData;
				m_reserved = newReserved;
			}
		}

		void resize(size_type newSize)
		{
			if (newSize > m_size)
				reserve(newSize);

			m_size = newSize;
		}

		void resize(size_type newSize, const value_type& value)
		{
			if (newSize > m_reserved)
				reserve(newSize);

			size_type index = m_size; //size before being resized
			m_size = newSize; //size is adjusted so operator[] works
			while (index < newSize) //value is filled in
			{
				this->operator[](index) = value;
				++index;
			}
		}

		template <typename... Ts> requires requires(Ts... args) {
			{ value_type(args...) } -> same_as<value_type>;
		}
		void emplace_back(Ts&&... args)
		{
			if (m_size == m_reserved)
				reserve((m_reserved > 0) ? (m_reserved * 2) : 1);

			++m_size;
			this->operator[](m_size - 1) = value_type(forward<Ts>(args)...);
		}

		void push_back(const value_type& value)
		{
			if (m_size == m_reserved)
				reserve((m_reserved > 0) ? (m_reserved * 2) : 1);

			++m_size;
			this->operator[](m_size - 1) = value;
		}

		void pop_back()
		{
			if (m_size == 0)
				throw runtime_error{ "Container is already empty." };

			--m_size;
		}

		template <typename... Ts> requires requires (Ts... args) {
			{ value_type(args...) } -> convertible_to<value_type>;
		}
		void emplace(iterator insertIter, Ts&&... args)
		{
			if (!PtrInData(&*insertIter))
				throw out_of_range{
					"The iterator you are seeking to insert a value at is out of bounds." };
			else if (insertIter == end())
			{
				emplace_back(forward<Ts>(args)...);
				return;
			}

			const size_type insertIndex = insertIter - begin();
			//compute before insertIter is potentially invalidated
			const size_type iterCount = m_size - insertIndex;

			if (m_size == m_reserved)
				reserve((m_reserved > 0) ? (m_reserved * 2) : 1);

			++m_size; //so operator[] works below
			for (size_type iter = 1; iter <= iterCount; ++iter)
				this->operator[](m_size - iter) = this->operator[](m_size - iter - 1);
			this->operator[](insertIndex) = value_type(forward<Ts>(args)...);
		}

		void insert(iterator insertIter, const value_type& value)
		{
			if (!PtrInData(&*insertIter))
				throw out_of_range{
					"The iterator you are seeking to insert a value at is out of bounds." };
			else if (insertIter == end())
			{
				push_back(value);
				return;
			}

			const size_type insertIndex = insertIter - begin();
			//compute before insertIter is potentially invalidated
			const size_type iterCount = m_size - insertIndex;

			if (m_size == m_reserved)
				reserve((m_reserved > 0) ? (m_reserved * 2) : 1);

			++m_size; //so operator[] works below
			for (size_type iter = 1; iter <= iterCount; ++iter)
				this->operator[](m_size - iter) = this->operator[](m_size - iter - 1);
			this->operator[](insertIndex) = value;
		}

		void insert(iterator insertIter, iterator start, iterator end)
		{
			if (!PtrInData(&*insertIter))
				throw out_of_range{
					"The iterator you are seeking to insert a value at is out of bounds." };
			else if (&*start > &*end)
				throw invalid_argument{ "The range you've provided should be reversed." };

			vector<T> temp;
			if (PtrInData(&*start) || PtrInData(&*end))
			{
				temp = vector<T>(start, end);
				start = temp.begin();
				end = temp.end();
			}

			const size_type insertIndex = insertIter - begin();
			const size_type addedElements = end - start;
			const size_type oldSize = m_size;
			const size_type newSize = m_size + addedElements;
			if (newSize > m_reserved)
				reserve(newSize);
			m_size = newSize; //so operator[] works below

			// Shift elements rightward, but do it BACKWARDS to avoid overwriting
			for (size_type index = oldSize; index > insertIndex; --index)
			{
				const size_type newIndex = index + addedElements - 1;
				this->operator[](newIndex) = this->operator[](index - 1);
			}

			// Insert new elements
			for (size_type iter = 0; iter < addedElements; ++iter)
				this->operator[](insertIndex + iter) = *(start + iter);
		}

		void insert(iterator insertIter, const_iterator start, const_iterator end)
		{
			if (!PtrInData(&*insertIter))
				throw out_of_range{
					"The iterator you are seeking to insert a value at is out of bounds." };
			else if (&*start > &*end)
				throw invalid_argument{ "The range you've provided should be reversed." };

			vector<T> temp;
			if (PtrInData(&*start) || PtrInData(&*end))
			{
				temp = vector<T>(start, end);
				start = temp.cbegin();
				end = temp.cend();
			}

			const size_type insertIndex = insertIter - begin();
			const size_type addedElements = end - start;
			const size_type oldSize = m_size;
			const size_type newSize = m_size + addedElements;
			if (newSize > m_reserved)
				reserve(newSize);
			m_size = newSize; //so operator[] works below

			// Shift elements rightward, but do it BACKWARDS to avoid overwriting
			for (size_type index = oldSize; index > insertIndex; --index)
			{
				const size_type newIndex = index + addedElements - 1;
				this->operator[](newIndex) = this->operator[](index - 1);
			}

			// Insert new elements
			for (size_type iter = 0; iter < addedElements; ++iter)
				this->operator[](insertIndex + iter) = *(start + iter);
		}

		void erase(iterator iter)
		{
			if (empty())
				throw runtime_error{ "Cannot remove elements from an already empty container." };
			else if (!PtrInData(&*iter))
				throw out_of_range{ "The iterator you are seeking to erase is out of bounds." };

			const size_type erasedIndex = iter - begin();

			for (size_type index = erasedIndex + 1; index < m_size; ++index)
				this->operator[](index - 1) = this->operator[](index);
			--m_size;
		}

		void erase(iterator start, iterator end)
		{
			if (!RangeInContainer(start, end))
				throw out_of_range{ "The range you're seeking to erase is out of bounds." };
			else if (empty())
				throw runtime_error{ "Cannot remove elements from an already empty container." };
			else if (&*start > &*end)
				throw invalid_argument{ "Arguments should be reversed." };

			const size_type rangeLength = end - start;
			const size_type endIndex = end - begin();

			for (size_type index = endIndex; index < m_size; ++index)
				this->operator[](index - rangeLength) = this->operator[](index);
			m_size -= rangeLength;
		}

		constexpr void clear() noexcept
		{
			m_size = 0;
		}

		void shrink_to_fit()
		{
			if (m_reserved > m_size)
			{
				vector<T> temp(m_size);

				for (size_type index = 0; index < m_size; ++index)
				{
					value_type& value = this->operator[](index);

					if constexpr (movable<T>)
						temp[index] = move(value);
					else
						temp[index] = value;
				}

				*this = move(temp);
			}
		}

		void swap(vector<T>& other) noexcept
		{
			if (this != &other)
			{
				vector<T> temp{ move(*this) };
				*this = move(other);
				other = move(temp);
			}
		}

	private:

		static constexpr void WriteToBuffer(T* buffer, const T* data, size_type size)
		{
			for (size_type i = 0; i < size; ++i)
				buffer[i] = data[i];
		}

		void DeallocateWithoutResize()
		{
			if (m_data)
				delete[] m_data;

			m_data = nullptr;
		}

		void DeallocateWithResize()
		{
			if (m_data)
				delete[] m_data;

			m_data = nullptr;
			m_size = m_reserved = 0;
		}

		void CopyData(const vector<T>& vec)
		{
			if (this != &vec)
			{
				if (m_reserved < vec.size())
				{
					DeallocateWithResize();
					m_size = m_reserved = vec.size();
					m_data = new T[m_reserved + 2];
				}
				else
					m_size = vec.size();

				for (size_type index = 0; index < vec.size(); ++index)
					this->operator[](index) = vec[index];
			}
		}

		void CheckBounds(size_type index) const
		{
			if (index >= m_size)
				throw out_of_range{ "Out of bounds." };
		}

		constexpr bool PtrInData(const value_type* ptr) const noexcept
		{
			return ptr && (ptr >= m_data) && (ptr <= m_data + m_size + 1);
		}

		constexpr bool RangeInContainer(iterator start, iterator end) const noexcept
		{
			return PtrInData(&*start) && PtrInData(&*end);
		}

		constexpr bool RangeInContainer(const_iterator start, const_iterator end) const noexcept
		{
			return PtrInData(&*start) && PtrInData(&*end);
		}

		constexpr bool RangeInContainer(reverse_iterator start, reverse_iterator end) const noexcept
		{
			return PtrInData(&*start) && PtrInData(&*end);
		}

		constexpr bool RangeInContainer(const_reverse_iterator start, const_reverse_iterator end) const noexcept
		{
			return PtrInData(&*start) && PtrInData(&*end);
		}

		value_type* m_data;
		size_type m_size;
		size_type m_reserved;
	};
}