#pragma once

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff
#define NOGDI                // No GDI (Graphics Device Interface) macros
#define NOMINMAX             // Prevent min/max macros
#define NOSERVICE            // No service APIs
#define NOHELP               // No Help APIs
#define NOMETAFILE           // No metafile APIs
#define NOMCX                // No Modem Configuration Extensions
#define NOIME                // No Input Method Editor
#define NOSOUND              // No Sound APIs
#define NOCOMM               // No serial communication APIs
#define NOKANJI              // No Kanji support
#define NOCRYPT              // No cryptography APIs
#define NOWH                 // No Windows hooks
#define NOPROFILER           // No profiler APIs
#define NODEFERWINDOWPOS     // No DeferWindowPos APIs
#define NOMEMMGR             // No memory manager APIs
#define NOKERNEL             // No Kernel APIs
#define NOUSER               // No User APIs
#define NONLS                // No National Language Support APIs
#define NOMB                 // No MessageBox macros
#define NODRAWTEXT           // No DrawText API
#define NOTEXTMETRIC         // No text metric APIs
#define NOMSG                // No message APIs
#define NOOPENFILE           // No OpenFile API
#define NORESOURCE           // No resource APIs
#define NOATOM               // No atom APIs
#define NOGDICAPMASKS        // No GDI capacity masks
#define NORASTEROPS          // No raster operations
#define NOSHOWWINDOW         // No ShowWindow API
#define NOWINOFFSETS         // No Get/SetWindowWord/Long functions
#define NOICONS              // No icon APIs
#define NOKEYSTATES          // No key state macros
#define NOSYSCOMMANDS        // No system commands
#define NORPC                // No RPC APIs
#define NOLOGERROR           // No logging/error APIs
#define NOPROXYSTUB          // No proxy/stub APIs
#define NOIMAGE              // No image APIs
#define NOCTLMGR             // No control manager APIs
#define NODEFERWINDOWPOS     // No DeferWindowPos API
#define NORPC                // No RPC APIs
#include "Windows.h"
#include "string_view.hpp"
#include "string.hpp"
#include "concepts.hpp"

namespace asv
{
	inline void print(char c)
	{
		static char buffer[2] = { '\0', '\0' };
		buffer[0] = c;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WriteConsoleA(hConsole, buffer, 1, nullptr, nullptr);
	}

	inline void print(string_view str)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WriteConsoleA(hConsole, str.data(), static_cast<DWORD>(str.size()), nullptr, nullptr);
	}

	template <typename numType> requires number<numType>
	inline void print(numType num)
	{
		print(to_string(num));
	}

	template <typename T>
	concept printable = convertible_to<T, string_view> || same_as<T, char> || number<T>;
}