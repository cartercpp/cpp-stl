#pragma once

#include "exception.hpp"
#include "concepts.hpp"

namespace asv
{
	//----------------------------FORWARD_ITERATOR----------------------------
	template <typename Container> requires requires() {
		typename Container::size_type;
		typename Container::value_type;
	}
	class forward_iterator
	{
	public:

		using size_type = typename Container::size_type;
		using value_type = typename Container::value_type;

		//CONSTRUCTORS & STUFF

		constexpr explicit forward_iterator(value_type* ptr) noexcept
			: m_ptr(ptr)
		{
		}

		//METHODS & STUFF

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

		forward_iterator& operator++()
		{
			CheckIfNull();
			++m_ptr;
			return *this;
		}

		forward_iterator operator++(int)
		{
			CheckIfNull();
			const forward_iterator temp = *this;
			this->operator++();
			return temp;
		}

		forward_iterator& operator+=(size_type count)
		{
			CheckIfNull();
			m_ptr += count;
			return *this;
		}

		forward_iterator& operator--()
		{
			CheckIfNull();
			--m_ptr;
			return *this;
		}

		forward_iterator operator--(int)
		{
			CheckIfNull();
			const forward_iterator temp = *this;
			this->operator--();
			return temp;
		}

		forward_iterator& operator-=(size_type count)
		{
			CheckIfNull();
			m_ptr -= count;
			return *this;
		}

	private:

		void CheckIfNull() const
		{
			if (!m_ptr)
				throw runtime_error{ "Cannot dereference an out-of-bounds iterator." };
		}

		friend constexpr bool operator==(forward_iterator<Container> lArg,
			forward_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr == rArg.m_ptr;
		}

		friend constexpr bool operator!=(forward_iterator<Container> lArg,
			forward_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr != rArg.m_ptr;
		}

		friend forward_iterator<Container> operator+(forward_iterator<Container> iter,
			size_type count)
		{
			return iter += count;
		}

		friend forward_iterator<Container> operator+(size_type count,
			forward_iterator<Container> iter)
		{
			return iter += count;
		}

		friend forward_iterator<Container> operator-(forward_iterator<Container> iter,
			size_type count)
		{
			return iter -= count;
		}

		friend constexpr long long operator-(forward_iterator<Container> lArg,
			forward_iterator<Container> rArg)
		{
			return lArg.m_ptr - rArg.m_ptr;
		}

		value_type* m_ptr;
	};
	//----------------------------FORWARD_ITERATOR----------------------------

	//----------------------------CONST_FORWARD_ITERATOR----------------------------
	template <typename Container>
	class const_forward_iterator
	{
	public:

		using size_type = typename Container::size_type;
		using value_type = const typename Container::value_type;

		//CONSTRUCTORS & STUFF

		constexpr explicit const_forward_iterator(value_type* ptr) noexcept
			: m_ptr(ptr)
		{
		}

		//METHODS & STUFF

		value_type& operator*() const
		{
			CheckIfNull();
			return *m_ptr;
		}

		const_forward_iterator& operator++()
		{
			CheckIfNull();
			++m_ptr;
			return *this;
		}

		const_forward_iterator operator++(int)
		{
			CheckIfNull();
			const const_forward_iterator temp = *this;
			this->operator++();
			return temp;
		}

		const_forward_iterator& operator+=(size_type count)
		{
			CheckIfNull();
			m_ptr += count;
			return *this;
		}

		const_forward_iterator& operator--()
		{
			CheckIfNull();
			--m_ptr;
			return *this;
		}

		const_forward_iterator operator--(int)
		{
			CheckIfNull();
			const const_forward_iterator temp = *this;
			this->operator--();
			return temp;
		}

		const_forward_iterator& operator-=(size_type count)
		{
			CheckIfNull();
			m_ptr -= count;
			return *this;
		}

	private:

		void CheckIfNull() const
		{
			if (!m_ptr)
				throw runtime_error{ "Cannot dereference an out-of-bounds iterator." };
		}

		friend constexpr bool operator==(const_forward_iterator<Container> lArg,
			const_forward_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr == rArg.m_ptr;
		}

		friend constexpr bool operator!=(const_forward_iterator<Container> lArg,
			const_forward_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr != rArg.m_ptr;
		}

		friend const_forward_iterator<Container> operator+(const_forward_iterator<Container> iter,
			size_type count)
		{
			return iter += count;
		}

		friend const_forward_iterator<Container> operator+(size_type count,
			const_forward_iterator<Container> iter)
		{
			return iter += count;
		}

		friend const_forward_iterator<Container> operator-(const_forward_iterator<Container> iter,
			size_type count)
		{
			return iter -= count;
		}

		friend constexpr long long operator-(const_forward_iterator<Container> lArg,
			const_forward_iterator<Container> rArg)
		{
			return lArg.m_ptr - rArg.m_ptr;
		}
		
		value_type* m_ptr;
	};
	//----------------------------CONST_FORWARD_ITERATOR----------------------------

	//----------------------------REVERSE_ITERATOR----------------------------
	template <typename Container>
	class reverse_iterator
	{
	public:

		using size_type = typename Container::size_type;
		using value_type = typename Container::value_type;

		//CONSTRUCTORS & STUFF

		constexpr explicit reverse_iterator(value_type* ptr) noexcept
			: m_ptr(ptr)
		{
		}

		//METHODS & STUFF

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

		reverse_iterator& operator++()
		{
			CheckIfNull();
			--m_ptr;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			CheckIfNull();
			const reverse_iterator temp = *this;
			this->operator++();
			return temp;
		}

		reverse_iterator& operator+=(size_type count)
		{
			CheckIfNull();
			m_ptr -= count;
			return *this;
		}

		reverse_iterator& operator--()
		{
			CheckIfNull();
			++m_ptr;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			CheckIfNull();
			const reverse_iterator temp = *this;
			this->operator--();
			return temp;
		}

		reverse_iterator& operator-=(size_type count)
		{
			CheckIfNull();
			m_ptr += count;
			return *this;
		}

	private:

		void CheckIfNull() const
		{
			if (!m_ptr)
				throw runtime_error{ "Cannot dereference an out-of-bounds iterator." };
		}

		friend constexpr bool operator==(reverse_iterator<Container> lArg,
			reverse_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr == rArg.m_ptr;
		}

		friend constexpr bool operator!=(reverse_iterator<Container> lArg,
			reverse_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr != rArg.m_ptr;
		}

		friend reverse_iterator<Container> operator+(reverse_iterator<Container> iter,
			size_type count)
		{
			return iter += count;
		}

		friend reverse_iterator<Container> operator+(size_type count,
			reverse_iterator<Container> iter)
		{
			return iter += count;
		}

		friend reverse_iterator<Container> operator-(reverse_iterator<Container> iter,
			size_type count)
		{
			return iter -= count;
		}

		friend constexpr long long operator-(reverse_iterator<Container> lArg,
			reverse_iterator<Container> rArg)
		{
			return rArg.m_ptr - lArg.m_ptr;
		}

		value_type* m_ptr;
	};
	//----------------------------REVERSE_ITERATOR----------------------------

	//----------------------------CONST_REVERSE_ITERATOR----------------------------
	template <typename Container>
	class const_reverse_iterator
	{
	public:

		using size_type = typename Container::size_type;
		using value_type = const typename Container::value_type;

		//CONSTRUCTORS & STUFF

		constexpr explicit const_reverse_iterator(value_type* ptr) noexcept
			: m_ptr(ptr)
		{
		}

		//METHODS & STUFF

		value_type& operator*() const
		{
			CheckIfNull();
			return *m_ptr;
		}

		const_reverse_iterator& operator++()
		{
			CheckIfNull();
			--m_ptr;
			return *this;
		}

		const_reverse_iterator operator++(int)
		{
			CheckIfNull();
			const const_reverse_iterator temp = *this;
			this->operator++();
			return temp;
		}

		const_reverse_iterator& operator+=(size_type count)
		{
			CheckIfNull();
			m_ptr -= count;
			return *this;
		}

		const_reverse_iterator& operator--()
		{
			CheckIfNull();
			++m_ptr;
			return *this;
		}

		const_reverse_iterator operator--(int)
		{
			CheckIfNull();
			const const_reverse_iterator temp = *this;
			this->operator--();
			return temp;
		}

		const_reverse_iterator& operator-=(size_type count)
		{
			CheckIfNull();
			m_ptr += count;
			return *this;
		}

	private:

		void CheckIfNull() const
		{
			if (!m_ptr)
				throw runtime_error{ "Cannot dereference an out-of-bounds iterator." };
		}

		friend constexpr bool operator==(const_reverse_iterator<Container> lArg,
			const_reverse_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr == rArg.m_ptr;
		}

		friend constexpr bool operator!=(const_reverse_iterator<Container> lArg,
			const_reverse_iterator<Container> rArg) noexcept
		{
			return lArg.m_ptr != rArg.m_ptr;
		}

		friend const_reverse_iterator<Container> operator+(const_reverse_iterator<Container> iter,
			size_type count)
		{
			return iter += count;
		}

		friend const_reverse_iterator<Container> operator+(size_type count,
			const_reverse_iterator<Container> iter)
		{
			return iter += count;
		}

		friend const_reverse_iterator<Container> operator-(const_reverse_iterator<Container> iter,
			size_type count)
		{
			return iter -= count;
		}

		friend constexpr long long operator-(const_reverse_iterator<Container> lArg,
			const_reverse_iterator<Container> rArg)
		{
			return rArg.m_ptr - lArg.m_ptr;
		}

		value_type* m_ptr;
	};
	//----------------------------CONST_REVERSE_ITERATOR----------------------------
}