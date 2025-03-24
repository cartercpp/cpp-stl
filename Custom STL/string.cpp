#include "string.hpp"
#include "utility.hpp"
#include "exception.hpp"

void asv::string::DefaultConstruct() noexcept
{
	m_data = new char[2] {'\0', '\0'};
	m_size = m_reserved = 0;
}

void asv::string::DeallocateWithoutResize() noexcept
{
	if (m_data)
		delete[] m_data;

	m_data = nullptr;
}

void asv::string::DeallocateWithResize() noexcept
{
	if (m_data)
		delete[] m_data;

	m_data = nullptr;
	m_size = m_reserved = 0;
}

void asv::string::AddNullTerminator()
{
	m_data[0] = '\0';
	m_data[m_size + 1] = '\0';
}

void asv::string::CheckBounds(size_type index) const
{
	if (index >= m_size)
		throw out_of_range{ "Out of bounds." };
}

asv::string::~string() noexcept
{
	DeallocateWithResize();
}

asv::string::string() noexcept
{
	DefaultConstruct();
}

asv::string::string(size_type size, char c)
{
	m_data = new char[size + 2];
	WriteBuffer(m_data + 1, size, c);
	m_size = m_reserved = size;
	AddNullTerminator();
}

asv::string::string(iterator start, iterator end)
{
	m_size = m_reserved = end - start;
	m_data = new char[m_reserved + 2];

	size_type index = 0;
	for (auto iter = start; iter != end; ++iter, ++index)
		this->operator[](index) = *iter;

	AddNullTerminator();
}

asv::string::string(const_iterator start, const_iterator end)
{
	m_size = m_reserved = end - start;
	m_data = new char[m_reserved + 2];

	size_type index = 0;
	for (auto iter = start; iter != end; ++iter, ++index)
		this->operator[](index) = *iter;

	AddNullTerminator();
}

asv::string::string(reverse_iterator start, reverse_iterator end)
{
	m_size = m_reserved = end - start;
	m_data = new char[m_reserved + 2];

	size_type index = 0;
	for (auto iter = start; iter != end; ++iter, ++index)
		this->operator[](index) = *iter;

	AddNullTerminator();
}

asv::string::string(const_reverse_iterator start, const_reverse_iterator end)
{
	m_size = m_reserved = end - start;
	m_data = new char[m_reserved + 2];

	size_type index = 0;
	for (auto iter = start; iter != end; ++iter, ++index)
		this->operator[](index) = *iter;

	AddNullTerminator();
}

asv::string::string(const char* str)
{
	const size_type size = Strlen(str);
	m_data = new char[size + 2];
	WriteBuffer(m_data + 1, str);
	m_size = m_reserved = size;
	//AddNullTerminator(); unnecessary b/c null terminator is written in call to WriteBuffer
}

asv::string::string(const string& other)
	: string{ other.data() }
{
}

asv::string& asv::string::operator=(const string& other)
{
	if (this != &other)
	{
		if (m_reserved < other.size())
		{
			DeallocateWithoutResize();
			m_reserved = other.size();
			m_data = new char[m_reserved + 2];
		}

		WriteBuffer(m_data + 1, other.data());
		m_size = other.size();
	}

	return *this;
}

asv::string::string(string&& other) noexcept
{
	m_data = other.m_data;
	m_size = other.m_size;
	m_reserved = other.m_reserved;
	other.m_data = nullptr;
	other.m_size = other.m_reserved = 0;
}

asv::string& asv::string::operator=(string&& other) noexcept
{
	if (this != &other)
	{
		DeallocateWithResize();
		m_data = other.m_data;
		m_size = other.m_size;
		m_reserved = other.m_reserved;
		other.m_data = nullptr;
		other.m_size = other.m_reserved = 0;
	}

	return *this;
}

void asv::string::swap(string& other) noexcept
{
	string temp{ move(*this) };
	*this = move(other);
	other = move(temp);
}

void asv::string::reserve(size_type newReserved)
{
	if (newReserved > m_reserved)
	{
		char* newData = new char[newReserved + 2];
		WriteBuffer(newData + 1, this->data());
		//AddNullTerminator(); unnecessary b/c null terminator is written in call to WriteBuffer
		DeallocateWithoutResize();
		m_data = newData;
		m_reserved = newReserved;
	}
}

void asv::string::resize(size_type newSize, char c)
{
	if (newSize > m_size)
	{
		char* newData = new char[newSize + 2];
		WriteBuffer(newData + 1, this->data());
		WriteBuffer(newData + 1 + m_size, newSize - m_size, c);
		DeallocateWithoutResize();
		m_data = newData;
		m_reserved = newSize;
	}

	m_size = newSize;
	AddNullTerminator();
}

void asv::string::push_back(char c)
{
	if (m_reserved == m_size)
		reserve((m_reserved > 0) ? (m_reserved * 2) : 1);

	++m_size; //so operator[] works
	this->operator[](m_size - 1) = c;
	AddNullTerminator();
}

void asv::string::insert(iterator insertIter, char value)
{
	if (!PtrInData(&*insertIter))
		throw out_of_range{
			"The iterator you are seeking to insert a value at is out of bounds." };
	else if (insertIter == end())
	{
		push_back(value);
		return;
	}

	const size_type insertIndex = insertIter - begin();
	//compute before insertIter is potentially invalidated
	const size_type iterCount = m_size - insertIndex;

	if (m_size == m_reserved)
		reserve((m_reserved > 0) ? (m_reserved * 2) : 1);

	++m_size; //so operator[] works below
	for (size_type iter = 1; iter <= iterCount; ++iter)
		this->operator[](m_size - iter) = this->operator[](m_size - iter - 1);
	this->operator[](insertIndex) = value;
	AddNullTerminator();
}

void asv::string::insert(iterator insertIter, iterator start, iterator end)
{
	if (!PtrInData(&*insertIter))
		throw out_of_range{
			"The iterator you are seeking to insert a value at is out of bounds." };
	else if (&*start > &*end)
		throw invalid_argument{ "The range you've provided should be reversed." };

	string temp;
	if (PtrInData(&*start) || PtrInData(&*end))
	{
		temp = string(start, end);
		start = temp.begin();
		end = temp.end();
	}

	const size_type insertIndex = insertIter - begin();
	const size_type addedElements = end - start;
	const size_type oldSize = m_size;
	const size_type newSize = m_size + addedElements;
	if (newSize > m_reserved)
		reserve(newSize);
	m_size = newSize; //so operator[] works below

	// Shift elements rightward, but do it BACKWARDS to avoid overwriting
	for (size_type index = oldSize; index > insertIndex; --index)
	{
		const size_type newIndex = index + addedElements - 1;
		this->operator[](newIndex) = this->operator[](index - 1);
	}

	// Insert new elements
	for (size_type iter = 0; iter < addedElements; ++iter)
		this->operator[](insertIndex + iter) = *(start + iter);
	AddNullTerminator();
}

void asv::string::insert(iterator insertIter, const_iterator start, const_iterator end)
{
	if (!PtrInData(&*insertIter))
		throw out_of_range{
			"The iterator you are seeking to insert a value at is out of bounds." };
	else if (&*start > &*end)
		throw invalid_argument{ "The range you've provided should be reversed." };

	string temp;
	if (PtrInData(&*start) || PtrInData(&*end))
	{
		temp = string(start, end);
		start = temp.cbegin();
		end = temp.cend();
	}

	const size_type insertIndex = insertIter - begin();
	const size_type addedElements = end - start;
	const size_type oldSize = m_size;
	const size_type newSize = m_size + addedElements;
	if (newSize > m_reserved)
		reserve(newSize);
	m_size = newSize; //so operator[] works below

	// Shift elements rightward, but do it BACKWARDS to avoid overwriting
	for (size_type index = oldSize; index > insertIndex; --index)
	{
		const size_type newIndex = index + addedElements - 1;
		this->operator[](newIndex) = this->operator[](index - 1);
	}

	// Insert new elements
	for (size_type iter = 0; iter < addedElements; ++iter)
		this->operator[](insertIndex + iter) = *(start + iter);
	AddNullTerminator();
}

void asv::string::erase(iterator iter)
{
	if (empty())
		throw runtime_error{ "Cannot remove elements from an already empty container." };
	else if (!PtrInData(&*iter))
		throw out_of_range{ "The iterator you are seeking to erase is out of bounds." };

	const size_type erasedIndex = iter - begin();

	for (size_type index = erasedIndex + 1; index < m_size; ++index)
		this->operator[](index - 1) = this->operator[](index);
	--m_size;
	AddNullTerminator();
}

void asv::string::erase(iterator start, iterator end)
{
	if (!RangeInContainer(start, end))
		throw out_of_range{ "The range you're seeking to erase is out of bounds." };
	else if (empty())
		throw runtime_error{ "Cannot remove elements from an already empty container." };
	else if (&*start > &*end)
		throw invalid_argument{ "Arguments should be reversed." };

	const size_type rangeLength = end - start;
	const size_type endIndex = end - begin();

	for (size_type index = endIndex; index < m_size; ++index)
		this->operator[](index - rangeLength) = this->operator[](index);
	m_size -= rangeLength;
	AddNullTerminator();
}

void asv::string::shrink_to_fit()
{
	if (m_reserved > m_size)
	{
		string temp(m_size, '\0');
		for (size_type index = 0; index < m_size; ++index)
			temp[index] = this->operator[](index);

		*this = move(temp);
	}

	AddNullTerminator();
}

void asv::string::replace(size_type index, size_type lengthToReplace, const string& str)
{
	if ((index + lengthToReplace) > m_size)
		throw out_of_range{ "Out of bounds." };

	string temp;
	string::const_iterator start = str.cbegin();
	string::const_iterator end = str.cend();

	if (this == &str)
	{
		temp = str;
		start = temp.cbegin();
		end = temp.cend();
	}

	if (lengthToReplace != str.size())
	{
		erase(begin() + index, begin() + index + lengthToReplace);
		insert(begin() + index, start, end);
	}
	else
		while (start != end)
		{
			this->operator[](index) = *start;
			++index;
			++start;
		}

	AddNullTerminator();
}

asv::string& asv::string::operator+=(const string& other)
{
	if (m_reserved < m_size + other.size())
		reserve(m_size + other.size());

	size_type insertIndex = m_size;
	m_size += other.size(); //so operator[] works

	for (size_type index = 0; index < other.size(); ++index, ++insertIndex)
		this->operator[](insertIndex) = other[index];
	AddNullTerminator();

	return *this;
}

asv::string asv::operator+(asv::string lArg, const asv::string& rArg)
{
	return lArg += rArg;
}

char& asv::string::operator[](size_type index)
{
	CheckBounds(index);
	return m_data[index + 1];
}

const char& asv::string::operator[](size_type index) const
{
	CheckBounds(index);
	return m_data[index + 1];
}