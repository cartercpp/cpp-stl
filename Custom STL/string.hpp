#pragma once

#include "algorithms.hpp"
#include "contiguous_iterator.hpp"
#include "vector.hpp"
#include "concepts.hpp"

namespace asv
{
	class string
	{
	public:

		using size_type = unsigned long long;
		using value_type = char;
		using iterator = asv::forward_iterator<string>;
		using const_iterator = asv::const_forward_iterator<string>;
		using reverse_iterator = asv::reverse_iterator<string>;
		using const_reverse_iterator = asv::const_reverse_iterator<string>;

		//CONSTRUCTORS & STUFF

		~string() noexcept;
		string() noexcept;
		explicit string(size_type, char);
		explicit string(iterator, iterator);
		explicit string(const_iterator, const_iterator);
		explicit string(reverse_iterator, reverse_iterator);
		explicit string(const_reverse_iterator, const_reverse_iterator);
		string(const char*);
		string(const string&);
		string& operator=(const string&);
		string(string&&) noexcept;
		string& operator=(string&&) noexcept;
		void swap(string&) noexcept;

		//METHODS & STUFF

		constexpr iterator begin() noexcept
		{
			return iterator{ m_data ? &this->operator[](0) : nullptr };
		}

		constexpr iterator end() noexcept
		{
			return iterator{ m_data ? (m_data + m_size + 1) : nullptr };
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator{ m_data ? &this->operator[](0) : nullptr };
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator{ m_data ? (m_data + m_size + 1) : nullptr };
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator{ m_data ? &this->operator[](0) : nullptr };
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator{ m_data ? (m_data + m_size + 1) : nullptr };
		}

		constexpr reverse_iterator rbegin() noexcept
		{
			return reverse_iterator{ m_data ? &this->operator[](m_size - 1) : nullptr };
		}

		constexpr reverse_iterator rend() noexcept
		{
			return reverse_iterator{ m_data };
		}

		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{ m_data ? &this->operator[](m_size - 1) : nullptr };
		}

		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{ m_data };
		}

		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{ m_data ? &this->operator[](m_size - 1) : nullptr };
		}

		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{ m_data };
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

		void reserve(size_type);
		void resize(size_type, char c = '\0');
		void push_back(char);
		void insert(iterator, char);
		void insert(iterator, iterator, iterator);
		void insert(iterator, const_iterator, const_iterator);
		void erase(iterator);
		void erase(iterator, iterator);
		
		constexpr void clear()
		{
			m_size = 0;
		}
		
		void shrink_to_fit();
		void replace(size_type, size_type, const string&);
		string& operator+=(const string&);

		char& operator[](size_type);
		const char& operator[](size_type) const;

		constexpr char* data() noexcept
		{
			return m_data ? (m_data + 1) : nullptr;
		}

		constexpr const char* data() const noexcept
		{
			return m_data ? (m_data + 1) : nullptr;
		}

	private:

		static constexpr size_type Strlen(const char* str)
		{
			size_type length = 0;

			if (str)
				while (*str != '\0')
				{
					++length;
					++str;
				}

			return length;
		}

		static constexpr void WriteBuffer(char* buffer, size_type size, char c)
		{
			for (size_type index = 0; index < size; ++index)
				buffer[index] = c;
		}

		static constexpr void WriteBuffer(char* buffer, const char* str)
		{
			while (*str != '\0')
			{
				*buffer = *str;
				++str;
				++buffer;
			}

			*buffer = '\0';
		}

		static constexpr void WriteBufferN(char* buffer, const char* data, size_type size)
		{
			for (size_type i = 0; i < size; ++i)
				buffer[i] = data[i];
		}

		constexpr bool PtrInData(const char* ptr) const noexcept
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

		void DeallocateWithResize() noexcept;
		void DeallocateWithoutResize() noexcept;
		void DefaultConstruct() noexcept;
		void AddNullTerminator();
		void CheckBounds(size_type) const;

		char* m_data;
		size_type m_size;
		size_type m_reserved;
	};

	string operator+(string, const string&);

	template <typename T> requires convertible_to<T, string>
	string to_string(const T& arg)
	{
		if constexpr (static_castable<T, string>)
			return static_cast<string>(arg);
		else if constexpr (value_initializable<T, string>)
			return string{ arg };
		else
			return string(arg);

		return ""; //never reached
	}

	inline string to_string(char c)
	{
		return string(1, c);
	}

	template <typename numType> requires integral<numType>
	string to_string(numType num)
	{
		if (num < 0)
			return "-" + to_string(0 - num);
		else if (num == 0)
			return "0";

		string output;
		output.reserve(10);

		while (num > 0)
		{
			output.push_back('0' + (num % 10));
			num /= 10;
		}

		for (string::size_type index = 0; index < output.size() / 2; ++index)
		{
			const char temp = output[index];
			output[index] = output[output.size() - index - 1];
			output[output.size() - index - 1] = temp;
		}

		return output;
	}

	template <typename numType> requires floating_point<numType>
	string to_string(numType num)
	{
		if (num < 0)
			return "-" + to_string(0 - num);

		const long long integerPart = static_cast<long long>(num);
		const numType decimalPart = num - integerPart;

		return to_string(integerPart) + "." + to_string(static_cast<int>(decimalPart * 100'000));
	}
}