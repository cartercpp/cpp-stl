#pragma once

#include "utility.hpp"
#include "type_traits.hpp"

namespace asv
{
	template <typename T, typename T2>
	concept same_as = is_same_v<T, T2>;

	template <typename From, typename To>
	concept static_castable = requires(From value) {
		{ static_cast<To>(value) } -> same_as<To>;
	};

	template <typename From, typename To>
	concept value_initializable = requires(From value) {
		{ To(value) } -> same_as<To>;
	};

	template <typename From, typename To>
	concept braced_initializable = requires(From value) {
		{ To{ value } } -> same_as<To>;
	};

	template <typename From, typename To>
	concept convertible_to = static_castable<From, To> || value_initializable<From, To>
		|| braced_initializable<From, To>;

	template <typename T>
	concept is_const = is_const_v<T>; //must use is_const_v

	template <typename T>
	concept is_volatile = is_volatile_v<T>; //must use is_volatile_v

	template <typename T>
	concept is_reference = is_reference_v<T>; //must use is_reference_v<T>

	template <typename T>
	concept is_const_volatile = is_const<T> && is_volatile<T>;

	template <typename T>
	concept is_const_reference = is_const<T> && is_reference<T>;

	template <typename T>
	concept is_volatile_reference = is_volatile<T> && is_reference<T>;

	template <typename T>
	concept is_const_volatile_reference = is_const_volatile<T> && is_reference<T>;

	template <typename T>
	concept is_one_way_iterator = requires(remove_cvref_t<T> iter, remove_cvref_t<T> iter2) {
		typename T::value_type;

		{ *iter } -> same_as<typename T::value_type&>;
		{ ++iter } -> convertible_to<remove_cvref_t<T>>;
		{ iter++ } -> convertible_to<remove_cvref_t<T>>;
		
		{ iter == iter2 } -> same_as<bool>;
		{ iter != iter2 } -> same_as<bool>;
	};

	template <typename T>
	concept is_bidirectional_iterator = is_one_way_iterator<T> && requires(remove_cvref_t<T> iter) {
		{ --iter } -> convertible_to<remove_cvref_t<T>>;
		{ iter-- } -> convertible_to<remove_cvref_t<T>>;
	};

	template <typename T>
	concept is_iterator = is_one_way_iterator<T> || is_bidirectional_iterator<T>;

	template <typename T>
	concept floating_point = same_as<remove_cvref_t<T>, float>
		|| same_as<remove_cvref_t<T>, double>
		|| same_as<remove_cvref_t<T>, long double>;

	template <typename T>
	concept signed_integral = same_as<remove_cvref_t<T>, short>
		|| same_as<remove_cvref_t<T>, int>
		|| same_as<remove_cvref_t<T>, long>
		|| same_as<remove_cvref_t<T>, long long>;

	template <typename T>
	concept unsigned_integral = same_as<remove_cvref_t<T>, unsigned short>
		|| same_as<remove_cvref_t<T>, unsigned int>
		|| same_as<remove_cvref_t<T>, unsigned long>
		|| same_as<remove_cvref_t<T>, unsigned long long>;

	template <typename T>
	concept integral = signed_integral<T> || unsigned_integral<T>;

	template <typename T>
	concept number = floating_point<T> || integral<T>;

	template <typename T>
	concept default_constructible = requires() {
		{ T{} } -> same_as<T>;
	};

	template <typename T>
	concept move_constructible = requires (T arg) {{ T{ move(arg) } } -> same_as<T>;}
		|| requires (T arg) { {T(move(arg)) } -> same_as<T>; };

	template <typename T>
	concept move_assignable = requires(T lArg, T rArg) {
		{ lArg = move(rArg) } -> same_as<T&>;
	};

	template <typename T>
	concept movable = move_constructible<T> && move_assignable<T>;

	template <typename T>
	concept copy_constructible = requires(T arg) {
		{ T{ arg } } -> same_as<T&>;
	};

	template <typename T>
	concept copy_assignable = requires(T lArg, T rArg) {
		{ lArg = rArg } -> same_as<T&>;
	};

	template <typename T>
	concept copyable = copy_constructible<T> && copy_assignable<T>;

	template <typename T>
	concept assignable = move_assignable<T> || copy_assignable<T>;
}