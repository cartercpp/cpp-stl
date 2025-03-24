#pragma once

#include "utility.hpp"
#include "algorithms.hpp"
#include "binary.hpp"
#include "vector.hpp"
#include "concepts.hpp"

namespace asv
{
	class big_uint
	{
	private:

		using size_type = unsigned long long;

	public:

		//CONSTRUCTORS & STUFF

		big_uint() noexcept;

		template <typename numType> requires integral<numType>
		big_uint(numType num)
		{
			const size_type numTypeBits = sizeof(numType) * 8;
			m_bits.resize(numTypeBits, false);
			
			numType bitValue = 1;
			for (size_type iter = 1; iter <= numTypeBits; ++iter)
			{
				const size_type bitIndex = numTypeBits - iter;
				m_bits.bit(bitIndex, (num & bitValue) != 0);
				bitValue *= 2;
			}
		}

		//METHODS & STUFF

		template <typename numType> requires integral<numType>
		explicit operator numType() const noexcept //noexcept b/c no check for overflow/underflow
		{
			const size_type numTypeBits = sizeof(numType) * 8;
			const size_type startBitIndex = (m_bits.size() > numTypeBits)
				? (m_bits.size() - numTypeBits) : 0;
			
			const size_type iterCount = m_bits.size() - startBitIndex;
			numType output = 0;
			numType bitValue = 1;

			for (size_type iter = 1; iter <= iterCount; ++iter)
			{
				const size_type bitIndex = m_bits.size() - iter;

				if (m_bits.bit(bitIndex))
					output += bitValue;

				bitValue *= 2;
			}

			return output;
		}

		big_uint& operator*=(const big_uint&) noexcept;
		big_uint& operator/=(const big_uint&);
		big_uint& operator+=(const big_uint&) noexcept;
		big_uint& operator-=(big_uint) noexcept;

	private:

		static void AddBinary(binary&, const binary&) noexcept;
		
		friend big_uint operator*(const big_uint& lArg, const big_uint& rArg) noexcept
		{
			vector<big_uint> components;

			for (size_type iter = 1; iter <= lArg.m_bits.size(); ++iter)
			{
				const size_type zeroesToAdd = iter - 1;
				const size_type lArgBitIndex = lArg.m_bits.size() - iter;
				const bool valueAtLArgBitIndex = lArg.m_bits.bit(lArgBitIndex);

				big_uint component;
				component.m_bits.reserve(rArg.m_bits.size() + zeroesToAdd);

				for (size_type rArgBitIndex = 0; rArgBitIndex < rArg.m_bits.size(); ++rArgBitIndex)
				{
					const bool valueAtRArgBitIndex = rArg.m_bits.bit(rArgBitIndex);
					component.m_bits.push_back(valueAtLArgBitIndex * valueAtRArgBitIndex);
				}

				component.m_bits.insertAll(
					binary(zeroesToAdd, false)
				);

				components.emplace_back(
					move(component)
				);
			}

			big_uint output;
			for (const big_uint& component : components)
				output += component;

			return output;
		}

		friend big_uint operator/(big_uint lArg, const big_uint& rArg)
		{
			return lArg /= rArg;
		}

		friend big_uint operator+(big_uint lArg, const big_uint& rArg) noexcept
		{
			return lArg += rArg;
		}

		friend big_uint operator-(big_uint lArg, const big_uint& rArg) noexcept
		{
			return lArg -= rArg;
		}

		friend bool operator==(const big_uint& lArg, const big_uint& rArg) noexcept
		{
			const size_type iterCount = (lArg.m_bits.size() > rArg.m_bits.size()) ?
				lArg.m_bits.size() : rArg.m_bits.size();
			const size_type lArgBits = lArg.m_bits.size(),
				rArgBits = rArg.m_bits.size();

			for (size_type iter = 1; iter <= iterCount; ++iter)
			{
				const bool lArgBit = (lArgBits >= iter) ? lArg.m_bits.bit(lArgBits - iter) : false,
					rArgBit = (rArgBits >= iter) ? rArg.m_bits.bit(rArgBits - iter) : false;

				if (lArgBit != rArgBit)
					return false;
			}

			return true;
		}

		friend bool operator!=(const big_uint& lArg, const big_uint& rArg) noexcept
		{
			return !(lArg == rArg);
		}

		friend bool operator>(const big_uint& lArg, const big_uint& rArg) noexcept
		{
			const size_type differenceInSize = (lArg.m_bits.size() > rArg.m_bits.size())
				? (lArg.m_bits.size() - rArg.m_bits.size())
				: (rArg.m_bits.size() - lArg.m_bits.size());

			const size_type lArgBitIndex = (lArg.m_bits.size() > rArg.m_bits.size())
				? lArg.m_bits.find(true) : (lArg.m_bits.find(true) + differenceInSize);
			const size_type rArgBitIndex = (rArg.m_bits.size() > lArg.m_bits.size())
				? rArg.m_bits.find(true) : (rArg.m_bits.find(true) + differenceInSize);

			return lArgBitIndex > rArgBitIndex;
		}

		friend bool operator>=(const big_uint& lArg, const big_uint& rArg) noexcept
		{
			return (lArg > rArg) || (lArg == rArg);
		}

		friend bool operator<(const big_uint& lArg, const big_uint& rArg) noexcept
		{
			const size_type differenceInSize = (lArg.m_bits.size() > rArg.m_bits.size())
				? (lArg.m_bits.size() - rArg.m_bits.size())
				: (rArg.m_bits.size() - lArg.m_bits.size());

			const size_type lArgBitIndex = (lArg.m_bits.size() > rArg.m_bits.size())
				? lArg.m_bits.find(true) : (lArg.m_bits.find(true) + differenceInSize);
			const size_type rArgBitIndex = (rArg.m_bits.size() > lArg.m_bits.size())
				? rArg.m_bits.find(true) : (rArg.m_bits.find(true) + differenceInSize);

			return lArgBitIndex < rArgBitIndex;
		}

		friend bool operator<=(const big_uint& lArg, const big_uint& rArg) noexcept
		{
			return (lArg < rArg) || (lArg == rArg);
		}

		binary m_bits;
	};
}