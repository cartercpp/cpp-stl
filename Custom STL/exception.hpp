#pragma once

namespace asv
{
	class exception
	{
	public:

		explicit exception(const char*) noexcept;
		const char* what() const noexcept;

	private:

		const char* m_message;
	};

	class logic_error : public exception
	{
	public:

		explicit logic_error(const char*) noexcept;
	};

	class invalid_argument : public logic_error
	{
	public:

		explicit invalid_argument(const char*) noexcept;
	};

	class domain_error : public logic_error
	{
	public:

		explicit domain_error(const char*) noexcept;
	};

	class length_error : public logic_error
	{
	public:

		explicit length_error(const char*) noexcept;
	};

	class out_of_range : public logic_error
	{
	public:

		explicit out_of_range(const char*) noexcept;
	};

	class runtime_error : public exception
	{
	public:

		explicit runtime_error(const char*) noexcept;
	};

	class range_error : public runtime_error
	{
	public:

		explicit range_error(const char*) noexcept;
	};

	class overflow_error : public runtime_error
	{
	public:

		explicit overflow_error(const char*) noexcept;
	};

	class underflow_error : public runtime_error
	{
	public:

		explicit underflow_error(const char*) noexcept;
	};

	class bad_alloc : public exception
	{
	public:

		explicit bad_alloc(const char*) noexcept;
	};
}