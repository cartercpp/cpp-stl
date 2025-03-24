#pragma once

#include "safe_math.hpp"
#include "concepts.hpp"

namespace asv
{
	namespace calculus
	{
		template <typename numType> requires floating_point<numType>
		numType integral(auto func, numType start, numType end, numType squareWidth = 0.001)
			requires requires(decltype(func) func, numType x) {
				{ func(x) } -> convertible_to<numType>;
			}
		{
			numType areaUnderCurve = 0;

			for (numType xValue = start; xValue < end; xValue += squareWidth)
			{
				const numType squareHeight = func(xValue);
				const numType squareArea = safe::multiply(squareWidth, squareHeight);
				areaUnderCurve = safe::add(areaUnderCurve, squareArea);
			}

			return safe::divide(areaUnderCurve, end - start);
		}

		template <typename numType> requires floating_point<numType>
		numType derivative(auto func, numType xValue)
			requires requires(decltype(func) func, numType x) {
				{ func(x) } -> convertible_to<numType>;
			}
		{
			return (func(xValue + 0.00001) - func(xValue)) / 0.00001;
		}
	}
}