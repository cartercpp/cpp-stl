#pragma once

#include "string.hpp"
#include "utility.hpp"
#include "print.hpp"

namespace asv
{
	template <printable... Ts>
	string format(string str, Ts&&... args)
	{
		using size_type = string::size_type;

		vector<string> argsAsStrings{ to_string(forward<Ts>(args))... };
		size_type argNumber = 0;

		for (size_type iter = 2; iter <= str.size(); ++iter)
		{
			const size_type index = str.size() - iter;
			const char c = str[index],
				c2 = str[index + 1];

			if ((c == '{') && (c2 == '}'))
			{
				str.replace(index, 2, argsAsStrings[argsAsStrings.size() - argNumber - 1]);
				++argNumber;
			}
		}

		return str;
	}
}