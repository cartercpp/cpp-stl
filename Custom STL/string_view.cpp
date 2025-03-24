#include "string_view.hpp"
#include "exception.hpp"

const char& asv::string_view::operator[](size_type index) const
{
	CheckBounds(index);
	return m_str[index];
}

void asv::string_view::CheckBounds(size_type index) const
{
	if (index >= m_size)
		throw out_of_range{ "Out of bounds." };
}