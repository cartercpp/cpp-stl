#pragma once

#include "exception.hpp"
#include "concepts.hpp"
#include "limits.hpp"

namespace asv
{
	namespace safe
	{
		template <typename numType> requires unsigned_integral<numType>
		numType add(numType lArg, numType rArg)
		{
			if (!(lArg <= asv::numeric_limits<numType>::max() - rArg))
				throw overflow_error{ "Output will overflow" };

			return lArg + rArg;
		}

		template <typename numType> requires signed_integral<numType>
		numType add(numType lArg, numType rArg)
		{
			if ((lArg > 0) && (rArg > 0) && !(lArg <= asv::numeric_limits<numType>::max() - rArg))
				throw overflow_error{ "Output will overflow" };
			else if ((lArg < 0) && (rArg < 0) && !(lArg >= asv::numeric_limits<numType>::lowest() - rArg))
				throw underflow_error{ "Output will underflow" };

			return lArg + rArg;
		}

		//--------------------------------------------------

		template <typename numType> requires unsigned_integral<numType>
		numType subtract(numType lArg, numType rArg)
		{
			if (rArg > lArg)
				throw underflow_error{ "Output will underflow" };

			return lArg - rArg;
		}

		template <typename numType> requires signed_integral<numType>
		numType subtract(numType lArg, numType rArg)
		{
			if ((lArg < 0) && (rArg > 0) && !(lArg >= asv::numeric_limits<numType>::lowest() + rArg))
				throw underflow_error{ "Output will underflow" };

			return lArg - rArg;
		}

		//--------------------------------------------------

		template <typename numType> requires unsigned_integral<numType>
		numType multiply(numType lArg, numType rArg)
		{
			if ((rArg != 0) && !(lArg <= asv::numeric_limits<numType>::max() / rArg))
				throw overflow_error{ "Output will overflow" };

			return lArg * rArg;
		}

		template <typename numType> requires signed_integral<numType>
		numType multiply(numType lArg, numType rArg)
		{
			if ((lArg > 0) && (rArg > 0) && !(lArg <= asv::numeric_limits<numType>::max() / rArg))
				throw overflow_error{ "Output will overflow" };
			else if ((lArg < 0) && (rArg < 0)
				&& ((lArg == asv::numeric_limits<numType>::lowest())
					|| (rArg == asv::numeric_limits<numType>::lowest())
					|| !(-lArg <= asv::numeric_limits<numType>::max() / -rArg)))
				throw overflow_error{ "Output will overflow" };
			else if ((lArg < 0) && (rArg > 0) && !(lArg >= asv::numeric_limits<numType>::max() / rArg))
				throw underflow_error{ "Output will underflow" };
			else if ((lArg > 0) && (rArg < 0) && !(rArg >= asv::numeric_limits<numType>::max() / lArg))
				throw underflow_error{ "Output will underflow" };

			return lArg * rArg;
		}

		//--------------------------------------------------

		template <typename numType> requires integral<numType>
		numType divide(numType lArg, numType rArg)
		{
			if (rArg == 0)
				throw invalid_argument{ "Cannot divide by 0" };

			return lArg / rArg;
		}

		//--------------------------------------------------
	}
}