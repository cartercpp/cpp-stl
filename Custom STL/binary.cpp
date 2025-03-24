#include "exception.hpp"
#include "string_view.hpp"
#include "vector.hpp"
#include "limits.hpp"
#include "binary.hpp"

asv::binary::binary(size_type size, bool value) noexcept
	: m_binaryChunks((size % numTypeBits == 0) ? (size / numTypeBits) : (size / numTypeBits + 1),
		value ? numeric_limits<numType>::max() : 0),
	m_size(size)
{
}

asv::binary::binary(string_view binaryStr)
	: m_binaryChunks((binaryStr.size()  % numTypeBits == 0) ? (binaryStr.size() / numTypeBits)
		: (binaryStr.size() / numTypeBits + 1), 0),
	m_size(binaryStr.size())
{
	size_type bitIndex = 0;

	for (const char c : binaryStr)
	{
		if ((c != '0') && (c != '1'))
			throw invalid_argument{ "A binary string can only contain 1s and 0s" };

		this->bit(bitIndex, c == '1');
		++bitIndex;
	}
}

bool asv::binary::bit(size_type bitIndex) const
{
	CheckBounds(bitIndex);
	
	const size_type chunkIndex = bitIndex / numTypeBits;
	const numType chunk = m_binaryChunks[chunkIndex];
	numType bitValue = 1;
	bitValue <<= numTypeBits - (bitIndex % numTypeBits) - 1;

	return (chunk & bitValue) != 0;
}

void asv::binary::bit(size_type bitIndex, bool value)
{
	CheckBounds(bitIndex);

	if (bit(bitIndex) != value)
	{
		const size_type chunkIndex = bitIndex / numTypeBits;
		numType& chunk = m_binaryChunks[chunkIndex];
		numType bitValue = 1;
		bitValue <<= numTypeBits - (bitIndex % numTypeBits) - 1;

		if (value)
			chunk += bitValue;
		else
			chunk -= bitValue;
	}
}

asv::binary& asv::binary::operator&=(const binary& other) noexcept
{
	for (size_type iter = 1; iter <= m_size; ++iter)
	{
		const bool otherBit = (iter <= other.size()) ? other.bit(other.size() - iter) : false;
		this->bit(m_size - iter, this->bit(m_size - iter) && otherBit);
	}

	return *this;
}

asv::binary& asv::binary::operator|=(const binary& other) noexcept
{
	for (size_type iter = 1; iter <= m_size; ++iter)
	{
		const bool otherBit = (iter <= other.size()) ? other.bit(other.size() - iter) : false;
		this->bit(m_size - iter, this->bit(m_size - iter) || otherBit);
	}

	return *this;
}

asv::binary& asv::binary::operator^=(const binary& other) noexcept
{
	for (size_type iter = 1; iter <= m_size; ++iter)
	{
		const bool otherBit = (iter <= other.size()) ? other.bit(other.size() - iter) : false;
		this->bit(m_size - iter, this->bit(m_size - iter) != otherBit);
	}

	return *this;
}

asv::binary::size_type asv::binary::find(bool value) const noexcept
{
	for (size_type bitIndex = 0; bitIndex < m_size; ++bitIndex)
		if (this->bit(bitIndex) == value)
			return bitIndex;

	return m_size;
}

asv::binary::size_type asv::binary::find(const binary& bits) const noexcept
{
	if (!bits.empty())
		for (size_type bitIndex = 0; bitIndex + bits.size() <= m_size; ++bitIndex)
		{
			bool foundMatch = true;

			for (size_type i = 0; i < bits.size(); ++i)
				if (this->bit(bitIndex + i) != bits.bit(i))
				{
					foundMatch = false;
					break;
				}

			if (foundMatch)
				return bitIndex;
		}

	return m_size;
}

asv::binary::size_type asv::binary::rfind(bool value) const noexcept
{
	for (size_type iter = 1; iter <= m_size; ++iter)
	{
		const size_type bitIndex = m_size - iter;

		if (this->bit(bitIndex) == value)
			return bitIndex;
	}

	return m_size;
}

asv::binary::size_type asv::binary::rfind(const binary& bits) const noexcept
{
	if (m_size >= bits.size())
	{
		const size_type iterCount = m_size - bits.size();

		for (size_type iter = 0; iter < iterCount; ++iter)
		{
			const size_type startBitIndex = m_size - bits.size() - iter;
			bool foundMatch = true;

			for (size_type i = 0; i < bits.size(); ++i)
				if (this->bit(startBitIndex + i) != bits.bit(i))
				{
					foundMatch = false;
					break;
				}

			if (foundMatch)
				return startBitIndex;
		}
	}

	return m_size;
}

void asv::binary::reserve(size_type bitCount)
{
	m_binaryChunks.reserve((bitCount % numTypeBits == 0) ? (bitCount / numTypeBits)
		: (bitCount / numTypeBits + 1));
}

void asv::binary::resize(size_type newSize, bool value)
{
	const size_type oldSize = m_size;

	m_binaryChunks.resize((newSize % numTypeBits == 0) ? (newSize / numTypeBits)
		: (newSize / numTypeBits + 1));
	m_size = newSize;
	
	for (size_type index = oldSize; index < newSize; ++index)
		this->bit(index, value);
}

void asv::binary::insert(size_type insertIndex, bool value)
{
	if (insertIndex > m_size)
		throw out_of_range{
			"Cannot insert at an index that is greater than the size of the binary."};
	else if (insertIndex == m_size)
	{
		push_back(value);
		return;
	}
	else if (m_size % numTypeBits == 0)
		m_binaryChunks.emplace_back(0);

	const size_type elementsAfterInsertIndex = m_size - insertIndex; //must come before ++m_size
	++m_size; //so this->bit() works below
	for (size_type iter = 1; iter <= elementsAfterInsertIndex; ++iter)
		this->bit(m_size - iter, this->bit(m_size - iter - 1));
	this->bit(insertIndex, value);
}

void asv::binary::insertAll(const binary& other)
{
	reserve(m_size + other.size());
	const size_type oldSize = m_size;
	m_size += other.size(); //so the operations below work

	for (size_type otherBitIndex = 0; otherBitIndex < other.size(); ++otherBitIndex)
	{
		const size_type bitIndex = oldSize + otherBitIndex;
		this->bit(bitIndex, other.bit(otherBitIndex));
	}
}

//implement insertAll here

void asv::binary::invertAll() noexcept
{
	for (size_type bitIndex = 0; bitIndex < m_size; ++bitIndex)
		this->bit(bitIndex, !this->bit(bitIndex));
}

void asv::binary::push_back(bool value)
{
	if (m_size % numTypeBits == 0)
		m_binaryChunks.emplace_back(0);

	++m_size; //so this->bit() works
	this->bit(m_size - 1, value);
}

void asv::binary::pop_back()
{
	if (m_size == 0)
		throw runtime_error{ "Container is already empty" };

	--m_size;
}

void asv::binary::swap(binary& other) noexcept
{
	binary temp{ move(*this) };
	*this = move(other);
	other = move(temp);
}

void asv::binary::CheckBounds(size_type bitIndex) const
{
	if (bitIndex >= m_size)
		throw out_of_range{ "Out of bounds." };
}