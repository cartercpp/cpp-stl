#pragma once

#include "concepts.hpp"

namespace asv
{
	template <typename numType> requires number<numType>
	struct numeric_limits
	{
		static constexpr numType max() noexcept
		{
			if constexpr (unsigned_integral<numType>)
			{
				numType output = 0;
				--output;
				return output;
			}
			else if constexpr (signed_integral<numType>)
			{
				constexpr int numTypeBitCount = sizeof(numType) * 8;
				numType output = 0;
				numType bitValue = 1;

				for (int i = 0; i + 1 < numTypeBitCount; ++i)
				{
					output += bitValue;
					bitValue <<= 1;
				}

				return output;
			}
			else
			{
				if constexpr (sizeof(numType) == 4) // float
					return 3.402823466e+38f; // 2^128 * (2 - 2^-23)
				else if constexpr (sizeof(numType) == 8) // double
					return 1.7976931348623157e+308; // 2^1024 * (2 - 2^-52)
				else if constexpr (sizeof(numType) == 16) // long double
					return 1.7976931348623157e+308L;
				else
					return 0; // Default for unknown type
			}
		}

		static constexpr numType min() noexcept
		{
			if constexpr (unsigned_integral<numType>)
				return 0;
			else if constexpr (signed_integral<numType>)
				return numType(1) << (sizeof(numType) * 8 - 1);
			else
			{
				if constexpr (sizeof(numType) == 4) // float
					return 1.175494351e-38f;
				else if constexpr (sizeof(numType) == 8) // double
					return 2.2250738585072014e-308;
				else if constexpr (sizeof(numType) == 16) // long double
					return 2.2250738585072014e-308L;
				else
					return 0; // Default for unknown type
			}
		}

		static constexpr numType lowest() noexcept
		{
			if constexpr (unsigned_integral<numType>)
				return 0;
			else if constexpr (signed_integral<numType>)
				return numType(1) << (sizeof(numType) * 8 - 1);
			else
			{
				if constexpr (sizeof(numType) == 4) // float
					return -3.402823466e+38f;
				else if constexpr (sizeof(numType) == 8)
					return -1.7976931348623157e+308;
				else if constexpr (sizeof(numType) == 16) // long double
					return -1.7976931348623157e+308L;
				else
					return 0; // Default for unknown type
			}
		}
	};
}