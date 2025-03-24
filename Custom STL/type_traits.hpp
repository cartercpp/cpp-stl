#pragma once

namespace asv
{
	//_s naming convention is unique to asv

	template <typename T, typename T2>
	struct is_same_s
	{
		inline static constexpr bool value = false;
	};
	
	template <typename T>
	struct is_same_s<T, T>
	{
		inline static constexpr bool value = true;
	};

	template <typename T, typename T2>
	inline constexpr bool is_same_v = is_same_s<T, T2>::value;

	template <typename T>
	struct is_const_s
	{
		inline static constexpr bool value = false;
	};

	template <typename T>
	struct is_const_s<const T>
	{
		inline static constexpr bool value = true;
	};

	template <typename T>
	inline constexpr bool is_const_v = is_const_s<T>::value;

	template <typename T>
	struct is_volatile_s
	{
		inline static constexpr bool value = false;
	};

	template <typename T>
	struct is_volatile_s<volatile T>
	{
		inline static constexpr bool value = true;
	};

	template <typename T>
	inline constexpr bool is_volatile_v = is_volatile_s<T>::value;

	template <typename T>
	struct is_lvalue_reference_s
	{
		inline static constexpr bool value = false;
	};

	template <typename T>
	struct is_lvalue_reference_s<T&>
	{
		inline static constexpr bool value = true;
	};

	template <typename T>
	inline constexpr bool is_lvalue_reference_v = is_lvalue_reference_s<T>::value;

	template <typename T>
	struct is_rvalue_reference_s
	{
		inline static constexpr bool value = false;
	};

	template <typename T>
	struct is_rvalue_reference_s<T&&>
	{
		inline static constexpr bool value = true;
	};

	template <typename T>
	inline constexpr bool is_rvalue_reference_v = is_rvalue_reference_s<T>::value;

	template <typename T>
	struct is_reference_s
	{
		inline static constexpr bool value = false;
	};

	template <typename T>
	struct is_reference_s<T&>
	{
		inline static constexpr bool value = true;
	};

	template <typename T>
	struct is_reference_s<T&&>
	{
		inline static constexpr bool value = true;
	};

	template <typename T>
	inline constexpr bool is_reference_v = is_reference_s<T>::value;

	template <typename T>
	struct remove_const
	{
		using type = T;
	};

	template <typename T>
	struct remove_const<const T>
	{
		using type = T;
	};

	template <typename T>
	using remove_const_t = remove_const<T>::type;

	template <typename T>
	struct remove_reference
	{
		using type = T;
	};

	template <typename T>
	struct remove_reference<T&>
	{
		using type = T;
	};

	template <typename T>
	struct remove_reference<T&&>
	{
		using type = T;
	};

	template <typename T>
	using remove_reference_t = remove_reference<T>::type;

	template <typename T>
	using remove_const_reference_t = remove_const_t<remove_reference_t<T>>;

	template <typename T>
	struct remove_volatile
	{
		using type = T;
	};

	template <typename T>
	struct remove_volatile<volatile T>
	{
		using type = T;
	};

	template <typename T>
	using remove_volatile_t = remove_volatile<T>::type;

	template <typename T>
	using remove_cvref_t = remove_const_t<remove_volatile_t<remove_reference_t<T>>>;
}