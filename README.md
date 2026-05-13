# cpp-stl

A from-scratch reimplementation of core components of the C++ Standard Library. Zero external dependencies — everything is built on the language itself.

## What's implemented

**Containers**
- `vector` — contiguous, growable
- `forward_list` — singly linked
- `list` — doubly linked
- `stack` — adapter
- `string` — owning character buffer
- `string_view` — non-owning view

**Foundation**
- A subset of `<concepts>` — used to constrain the containers and algorithms in the rest of the library
- A subset of `<type_traits>`

## Goals and non-goals

The goal is to understand the C++ Standard Library by re-deriving it. Every container exposes the iterator category the standard requires, supports the full constructor set (default, copy, move, range, initializer-list), and is constrained via C++20 concepts rather than SFINAE.

The goal is **not** to replace `libstdc++` or MSVC STL. The library isn't optimized, isn't tested against libcxx's conformance suite, and isn't intended for production use.

## Companion content

A walkthrough is on YouTube: https://youtu.be/iRnyV7qUl4A

## Build

The project ships as a Visual Studio solution (`Custom STL.sln`). Open it in Visual Studio 2022 with the C++20 workload installed and build the `Custom STL` project.
