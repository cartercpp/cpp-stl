#pragma once

#include "type_traits.hpp"
#include "contiguous_iterator.hpp"
#include "concepts.hpp"

namespace asv
{
	template <typename T>
	class span
	{
	public:

		using value_type = T;
		using size_type = unsigned long long;
		//add iterators later?

		//CONSTRUCTORS & STUFF

		template <typename Container> requires requires(remove_cvref_t<Container> cont) {
			typename Container::value_type;
			typename Container::size_type;
			typename Container::iterator;
			typename Container::const_iterator;
			typename Container::reverse_iterator;
			typename Container::const_reverse_iterator;

			{ cont.begin() } -> same_as<typename Container::iterator>;
			{ cont.end() } -> same_as<typename Container::iterator>;
			{ cont.cbegin() } -> same_as<typename Container::const_iterator>;
			{ cont.cend() } -> same_as<typename Container::const_iterator>;
			{ cont.rbegin() } -> same_as<typename Container::reverse_iterator>;
			{ cont.rend() } -> same_as<typename Container::reverse_iterator>;
			{ cont.crbegin() } -> same_as<typename Container::const_reverse_iterator>;
			{ cont.crend() } -> same_as<typename Container::const_reverse_iterator>;
			{ cont.data() } -> same_as<typename Container::value_type*>;
			{ cont.size() } -> convertible_to<size_type>;
		}
		constexpr span(const Container& cont) noexcept(noexcept(cont.data()) && noexcept(cont.size()))
			: m_data(cont.data()), m_size(cont.size())
		{
		}

		//METHODS & STUFF

		constexpr const value_type& operator[](size_type index) const
		{
			return m_data[index];
		}

		constexpr size_type size() const noexcept
		{
			return m_size;
		}

	private:

		const value_type* m_data;
		size_type m_size;
	};
}