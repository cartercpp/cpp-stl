#include "binary.hpp"
#include "exception.hpp"
#include "concepts.hpp"
#include "big_uint.hpp"

asv::big_uint::big_uint() noexcept
	: m_bits(1, false)
{
}

asv::big_uint& asv::big_uint::operator*=(const big_uint& other) noexcept
{
	return *this = (*this * other);
}

asv::big_uint& asv::big_uint::operator/=(const big_uint& other)
{
	return *this; //change later
}

asv::big_uint& asv::big_uint::operator+=(const big_uint& other) noexcept
{
	AddBinary(m_bits, other.m_bits);
	return *this;
}

//									important to pass by value
asv::big_uint& asv::big_uint::operator-=(big_uint other) noexcept
{
	other.m_bits.invertAll();
	other += 1;
	return *this += other;
}

void asv::big_uint::AddBinary(binary& lArg, const binary& rArg) noexcept
{
	const size_type iterCount = (lArg.size() > rArg.size()) ? lArg.size() : rArg.size();
	bool carryBit = false;

	for (size_type iter = 1; iter <= iterCount; ++iter)
	{
		const bool lArgBit = (lArg.size() >= iter) ? lArg.bit(lArg.size() - iter) : false,
			rArgBit = (rArg.size() >= iter) ? rArg.bit(rArg.size() - iter) : false;
		const int oneBitCount = lArgBit + rArgBit + carryBit;

		switch (oneBitCount)
		{
		case 3:
		{
			if (lArg.size() >= iter)
				lArg.bit(lArg.size() - iter, true);
			else
				lArg.insert(0, true);

			//carryBit remains true
			break;
		}
		case 2:
		{
			if (lArg.size() >= iter)
				lArg.bit(lArg.size() - iter, false);
			else
				lArg.insert(0, false);

			carryBit = true;
			break;
		}
		case 1:
		{
			if (lArg.size() >= iter)
				lArg.bit(lArg.size() - iter, true);
			else
				lArg.insert(0, true);

			carryBit = false;
			break;
		}
		case 0:
		{
			if (lArg.size() >= iter)
				lArg.bit(lArg.size() - iter, false);
			else
				lArg.insert(0, false);

			//carryBit remains false
			break;
		}
		}
	}

	if (carryBit)
		lArg.insert(0, true);
}