#pragma once

#include "concepts.hpp"

namespace asv
{
	template <typename numType> requires number<numType>
	class complex
	{
	public:

		using value_type = numType;

		//CONSTRUCTORS & STUFF

		//add more constructors?

		//not explicit to allow for complex c = 1 (1 + 0i);
		constexpr complex(numType real, numType imaginary = 0) noexcept
			: m_real(real), m_imaginary(imaginary)
		{
		}

		//METHODS & STUFF

		constexpr numType real() const noexcept
		{
			return m_real;
		}

		constexpr void real(numType real) noexcept
		{
			m_real = real;
		}

		constexpr numType imaginary() const noexcept
		{
			return m_imaginary;
		}
		
		constexpr void imaginary(numType imaginary) noexcept
		{
			m_imaginary = imaginary;
		}

		constexpr complex<numType>& operator+=(const complex<numType>& other) noexcept
		{
			m_real += other.real();
			m_imaginary += other.imaginary();
			return *this;
		}

		constexpr complex<numType>& operator-=(const complex<numType>& other) noexcept
		{
			m_real -= other.real();
			m_imaginary -= other.imaginary();
			return *this;
		}

		constexpr complex<numType>& operator*=(const complex<numType>& other) noexcept
		{
			const numType a = m_real,
				b = m_imaginary,
				c = other.real(),
				d = other.imaginary();

			m_real = a * c - b * d;
			m_imaginary = b * c + a * d;

			return *this;
		}

		constexpr complex<numType>& operator/=(const complex<numType>& other) noexcept
		{
			const numType a = m_real,
				b = m_imaginary,
				c = other.real(),
				d = other.imaginary();

			m_real = (a * c + b * d) / (c * c + d * d);
			m_imaginary = (b * c - a * d) / (c * c + d * d);

			return *this;
		}

		constexpr complex<numType>& operator*=(numType scalar) noexcept
		{
			m_real *= scalar;
			m_imaginary *= scalar;

			return *this;
		}

		constexpr complex<numType>& operator/=(numType scalar) noexcept
		{
			m_real /= scalar;
			m_imaginary /= scalar;

			return *this;
		}

		//add more later

		void swap(complex<numType>& other) noexcept
		{
			complex<numType> temp{ *this };
			*this = other;
			other = temp;
		}

	private:

		friend constexpr bool operator==(const complex<numType>& lArg,
			const complex<numType>& rArg) noexcept
		{
			return (lArg.m_real == rArg.m_real) && (lArg.m_imaginary == rArg.m_imaginary);
		}

		friend constexpr bool operator!=(const complex<numType>& lArg,
			const complex<numType>& rArg) noexcept
		{
			return (lArg.m_real != rArg.m_real) || (lArg.m_imaginary != rArg.m_imaginary);
		}

		friend constexpr complex<numType> operator+(complex<numType> lArg,
			complex<numType> rArg) noexcept
		{
			return lArg += rArg;
		}

		friend constexpr complex<numType> operator-(complex<numType> lArg,
			complex<numType> rArg) noexcept
		{
			return lArg -= rArg;
		}

		friend constexpr complex<numType> operator*(complex<numType> lArg,
			complex<numType> rArg) noexcept
		{
			return lArg *= rArg;
		}

		friend constexpr complex<numType> operator/(complex<numType> lArg,
			complex<numType> rArg) noexcept
		{
			return lArg /= rArg;
		}

		friend constexpr complex<numType> operator*(complex<numType> complexNum,
			numType scalar) noexcept
		{
			return complexNum *= scalar;
		}

		friend constexpr complex<numType> operator*(numType scalar,
			complex<numType> complexNum) noexcept
		{
			return complexNum *= scalar;
		}

		friend constexpr complex<numType> operator/(complex<numType> complexNum,
			numType scalar) noexcept
		{
			return complexNum /= scalar;
		}

		numType m_real;
		numType m_imaginary;
	};

	namespace complex_literals
	{
		inline complex<unsigned long long> operator"" _i(unsigned long long iValue) noexcept
		{
			return complex<unsigned long long>(0, iValue);
		}

		inline complex<long double> operator"" _i(long double iValue) noexcept
		{
			return complex<long double>(0, iValue);
		}
	}
}