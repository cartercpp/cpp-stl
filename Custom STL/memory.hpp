#pragma once

#include "utility.hpp"
#include "exception.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T>
	class unique_ptr
	{
	public:

		using value_type = T;

		//CONSTRUCTORS & STUFF

		~unique_ptr()
		{
			reset();
		}

		constexpr unique_ptr() noexcept
			: m_ptr(nullptr)
		{
		}

		constexpr explicit unique_ptr(value_type* ptr) noexcept
			: m_ptr(ptr)
		{
		}

		unique_ptr(const unique_ptr<T>&) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

		constexpr unique_ptr(unique_ptr<T>&& other) noexcept
			: m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}

		unique_ptr<T>& operator=(unique_ptr<T>&& other) //not noexcept b/c reset may throw
		{
			if (this != &other)
			{
				reset();
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

		constexpr value_type* get() const noexcept
		{
			return m_ptr;
		}

		constexpr value_type* operator->() const noexcept
		{
			return m_ptr;
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

		void reset()
		{
			try
			{
				delete m_ptr;
				m_ptr = nullptr;
			}
			catch (...)
			{
				m_ptr = nullptr;
			}
		}

		constexpr value_type* release() noexcept
		{
			value_type* output = m_ptr;
			m_ptr = nullptr;
			return output;
		}

		void swap(unique_ptr<T>& other)
		{
			unique_ptr<T> temp{ move(*this) };
			*this = move(other);
			other = move(temp);
		}

	private:

		void CheckIfNull() const
		{
			if (!m_ptr)
				throw runtime_error{ "Cannot dereference a null pointer" };
		}

		friend bool operator==(const unique_ptr<T>& lArg, const unique_ptr<T>& rArg) noexcept
		{
			return lArg.m_ptr == rArg.m_ptr;
		}

		friend bool operator!=(const unique_ptr<T>& lArg, const unique_ptr<T>& rArg) noexcept
		{
			return lArg.m_ptr != rArg.m_ptr;
		}

		friend bool operator<=(const unique_ptr<T>& lArg, const unique_ptr<T>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr <= rArg.m_ptr);
		}

		friend bool operator<(const unique_ptr<T>& lArg, const unique_ptr<T>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr < rArg.m_ptr);
		}

		friend bool operator>=(const unique_ptr<T>& lArg, const unique_ptr<T>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr >= rArg.m_ptr);
		}

		friend bool operator>(const unique_ptr<T>& lArg, const unique_ptr<T>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr > rArg.m_ptr);
		}

		friend bool operator==(const unique_ptr<T>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr == rawPtr;
		}

		friend bool operator==(const T* rawPtr, const unique_ptr<T>& uPtr) noexcept
		{
			return uPtr.m_ptr == rawPtr;
		}

		friend bool operator!=(const unique_ptr<T>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr != rawPtr;
		}

		friend bool operator!=(const T* rawPtr, const unique_ptr<T>& uPtr) noexcept
		{
			return uPtr.m_ptr != rawPtr;
		}

		friend bool operator<=(const unique_ptr<T>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr <= rawPtr);
		}

		friend bool operator<=(const T* rawPtr, const unique_ptr<T>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr <= uPtr.m_ptr);
		}

		friend bool operator<(const unique_ptr<T>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr < rawPtr);
		}

		friend bool operator<(const T* rawPtr, const unique_ptr<T>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr < uPtr.m_ptr);
		}

		friend bool operator>=(const unique_ptr<T>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr >= rawPtr);
		}

		friend bool operator>=(const T* rawPtr, const unique_ptr<T>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr >= uPtr.m_ptr);
		}

		friend bool operator>(const unique_ptr<T>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr > rawPtr);
		}

		friend bool operator>(const T* rawPtr, const unique_ptr<T>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr > uPtr.m_ptr);
		}

		value_type* m_ptr;
	};

	template <typename T, typename... Ts> requires requires(Ts... args) {
		{ T(args...) } -> convertible_to<T>;
	}
	unique_ptr<T> make_unique(Ts&&... args)
	{
		alignas(T) char* buffer = new char[sizeof(T)];

		try
		{
			T* ptr = new (buffer) T(forward<Ts>(args)...);
			return unique_ptr<T>{ptr};
		}
		catch (...)
		{
			delete[] buffer;
			throw runtime_error{ "Exception thrown during heap allocation" };
		}

		return unique_ptr<T>{nullptr}; //never reached
	}

	//--------------------------------------------------------------------
	//--------------------------------------------------------------------
	//--------------------------------------------------------------------
	//--------------------------------------------------------------------
	//--------------------------------------------------------------------

	template <typename T>
	class unique_ptr<T[]>
	{
	public:

		using value_type = T;

		//CONSTRUCTORS & STUFF

		~unique_ptr()
		{
			reset();
		}

		constexpr unique_ptr() noexcept
			: m_ptr(nullptr)
		{
		}

		constexpr explicit unique_ptr(value_type* ptr) noexcept
			: m_ptr(ptr)
		{
		}

		unique_ptr(const unique_ptr<T[]>&) = delete;
		unique_ptr<T[]>& operator=(const unique_ptr<T[]>&) = delete;

		constexpr unique_ptr(unique_ptr<T[]>&& other) noexcept
			: m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}

		unique_ptr<T[]>& operator=(unique_ptr<T[]>&& other) //not noexcept b/c reset may throw
		{
			if (this != &other)
			{
				reset();
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

		constexpr value_type* get() const noexcept
		{
			return m_ptr;
		}

		constexpr value_type* operator->() const noexcept
		{
			return m_ptr;
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

		constexpr value_type& operator[](unsigned long long index)
		{
			return m_ptr[index];
		}
		
		constexpr const value_type& operator[](unsigned long long index) const
		{
			return m_ptr[index];
		}

		void reset()
		{
			try
			{
				delete[] m_ptr;
				m_ptr = nullptr;
			}
			catch (...)
			{
				m_ptr = nullptr;
			}
		}

		constexpr value_type* release() noexcept
		{
			value_type* output = m_ptr;
			m_ptr = nullptr;
			return output;
		}

		void swap(unique_ptr<T[]>& other)
		{
			unique_ptr<T[]> temp{ move(*this) };
			*this = move(other);
			other = move(temp);
		}

	private:

		void CheckIfNull() const
		{
			if (!m_ptr)
				throw runtime_error{ "Cannot dereference a null pointer" };
		}

		friend bool operator==(const unique_ptr<T[]>& lArg, const unique_ptr<T[]>& rArg) noexcept
		{
			return lArg.m_ptr == rArg.m_ptr;
		}

		friend bool operator!=(const unique_ptr<T[]>& lArg, const unique_ptr<T[]>& rArg) noexcept
		{
			return lArg.m_ptr != rArg.m_ptr;
		}

		friend bool operator<=(const unique_ptr<T[]>& lArg, const unique_ptr<T[]>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr <= rArg.m_ptr);
		}

		friend bool operator<(const unique_ptr<T[]>& lArg, const unique_ptr<T[]>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr < rArg.m_ptr);
		}

		friend bool operator>=(const unique_ptr<T[]>& lArg, const unique_ptr<T[]>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr >= rArg.m_ptr);
		}

		friend bool operator>(const unique_ptr<T[]>& lArg, const unique_ptr<T[]>& rArg) noexcept
		{
			return lArg.m_ptr && rArg.m_ptr && (lArg.m_ptr > rArg.m_ptr);
		}

		friend bool operator==(const unique_ptr<T[]>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr == rawPtr;
		}

		friend bool operator==(const T* rawPtr, const unique_ptr<T[]>& uPtr) noexcept
		{
			return uPtr.m_ptr == rawPtr;
		}

		friend bool operator!=(const unique_ptr<T[]>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr != rawPtr;
		}

		friend bool operator!=(const T* rawPtr, const unique_ptr<T[]>& uPtr) noexcept
		{
			return uPtr.m_ptr != rawPtr;
		}

		friend bool operator<=(const unique_ptr<T[]>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr <= rawPtr);
		}

		friend bool operator<=(const T* rawPtr, const unique_ptr<T[]>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr <= uPtr.m_ptr);
		}

		friend bool operator<(const unique_ptr<T[]>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr < rawPtr);
		}

		friend bool operator<(const T* rawPtr, const unique_ptr<T[]>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr < uPtr.m_ptr);
		}

		friend bool operator>=(const unique_ptr<T[]>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr >= rawPtr);
		}

		friend bool operator>=(const T* rawPtr, const unique_ptr<T[]>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr >= uPtr.m_ptr);
		}

		friend bool operator>(const unique_ptr<T[]>& uPtr, const T* rawPtr) noexcept
		{
			return uPtr.m_ptr && rawPtr && (uPtr.m_ptr > rawPtr);
		}

		friend bool operator>(const T* rawPtr, const unique_ptr<T[]>& uPtr) noexcept
		{
			return rawPtr && uPtr.m_ptr && (rawPtr > uPtr.m_ptr);
		}

		value_type* m_ptr;
	};

	template <typename T>
	unique_ptr<T[]> make_unique(unsigned long long elemCount)
	{
		alignas(T) char* buffer = new char[sizeof(T) * elemCount];

		try
		{
			T* ptr = new (buffer) T[elemCount];
			return unique_ptr<T[]>{ptr};
		}
		catch (...)
		{
			delete[] buffer;
			throw runtime_error{ "Exception thrown during heap allocation" };
		}

		return unique_ptr<T[]>{nullptr}; //never reached
	}
}