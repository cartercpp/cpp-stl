#include "algorithms.hpp"
#include "array.hpp"
#include "big_uint.hpp"
#include "binary.hpp"
#include "calculus.hpp"
#include "chrono.hpp"
#include "complex.hpp"
#include "concepts.hpp"
#include "contiguous_iterator.hpp"
#include "exception.hpp"
#include "format.hpp"
#include "forward_list.hpp"
#include "iterator.hpp"
#include "limits.hpp"
#include "lin_alg.hpp"
#include "list.hpp"
#include "math.hpp"
#include "memory.hpp"
#include "numbers.hpp"
#include "optional.hpp"
#include "print.hpp"
#include "random.hpp"
#include "safe_math.hpp"
#include "span.hpp"
#include "stack.hpp"
#include "string.hpp"
#include "string_view.hpp"
#include "tensor.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "vector.hpp"

int main()
{
	try
	{
		constexpr int n = asv::numeric_limits<int>::max();
		constexpr int n2 = asv::numeric_limits<int>::max();
		asv::print(asv::format("{} + {} = ", n, n2));

		const int output = asv::safe::add(n, n2);
		asv::print(output);
	}
	catch (asv::exception& e)
	{
		asv::print(e.what()); //2147483647 + 2147483647 = Output will overflow
	}

	return 0;
}