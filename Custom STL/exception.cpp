#include "exception.hpp"

asv::exception::exception(const char* message) noexcept
	: m_message{ message }
{
}

const char* asv::exception::what() const noexcept
{
	return m_message;
}

asv::logic_error::logic_error(const char* message) noexcept
	: exception{message}
{
}

asv::invalid_argument::invalid_argument(const char* message) noexcept
	: logic_error{ message }
{
}

asv::domain_error::domain_error(const char* message) noexcept
	: logic_error{ message }
{
}

asv::length_error::length_error(const char* message) noexcept
	: logic_error{ message }
{
}

asv::out_of_range::out_of_range(const char* message) noexcept
	: logic_error{ message }
{
}

asv::runtime_error::runtime_error(const char* message) noexcept
	: exception{ message }
{
}

asv::range_error::range_error(const char* message) noexcept
	: runtime_error{ message }
{
}

asv::overflow_error::overflow_error(const char* message) noexcept
	: runtime_error{ message }
{
}

asv::underflow_error::underflow_error(const char* message) noexcept
	: runtime_error{ message }
{
}

asv::bad_alloc::bad_alloc(const char* message) noexcept
	: exception{ message }
{
}