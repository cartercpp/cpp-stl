#pragma once

#include "string_view.hpp"
#include "vector.hpp"
#include "utility.hpp"
#include "concepts.hpp"

namespace asv
{
	class binary
	{
	private:

		using numType = unsigned int;
		inline static constexpr int numTypeBits = sizeof(numType) * 8;

	public:

		using size_type = unsigned long long;

		//CONSTRUCTORS & STUFF

		constexpr binary() noexcept
			: m_size(0)
		{
		}

		explicit binary(size_type, bool value = false) noexcept;
		binary(string_view);

		//METHODS & STUFF

		constexpr size_type size() const noexcept
		{
			return m_size;
		}

		constexpr bool empty() const noexcept
		{
			return m_size == 0;
		}

		bool bit(size_type) const;
		void bit(size_type, bool);

		//implement method that can convert binary to a number

		binary& operator&=(const binary&) noexcept;
		binary& operator|=(const binary&) noexcept;
		binary& operator^=(const binary&) noexcept;

		size_type find(bool) const noexcept;
		size_type find(const binary&) const noexcept;
		size_type rfind(bool) const noexcept;
		size_type rfind(const binary&) const noexcept;

		void reserve(size_type);
		void resize(size_type, bool value = false);
		void insert(size_type, bool);
		void insertAll(const binary&);
		//implement insertAll later
		//void insertAll(size_type, const binary&);
		void invertAll() noexcept;
		void push_back(bool);

		void pop_back();
		void swap(binary&) noexcept;

		constexpr void clear() noexcept
		{
			m_binaryChunks.clear();
			m_size = 0;
		}

	private:

		void CheckBounds(size_type) const;

		friend binary operator&(binary lArg, const binary& rArg) noexcept
		{
			return lArg &= rArg;
		}

		friend binary operator|(binary lArg, const binary& rArg) noexcept
		{
			return lArg |= rArg;
		}

		friend binary operator^(binary lArg, const binary& rArg) noexcept
		{
			return lArg ^= rArg;
		}

		friend bool operator==(const binary& lArg, const binary& rArg) noexcept
		{
			if (lArg.size() != rArg.size())
				return false;

			for (binary::size_type bitIndex = 0; bitIndex < lArg.size(); ++bitIndex)
				if (lArg.bit(bitIndex) != rArg.bit(bitIndex))
					return false;

			return true;
		}

		friend bool operator!=(const binary& lArg, const binary& rArg) noexcept
		{
			return !(lArg == rArg);
		}

		vector<numType> m_binaryChunks;
		size_type m_size;
	};
}