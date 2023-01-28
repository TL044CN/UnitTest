#pragma once
#ifndef UT_COMMON_H
#define UT_COMMON_H
#if __cplusplus > 201703L
#include <string_view>
#else
#include <string>
#endif

#if defined(__WIN32) or defined(WIN32)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

namespace Test {
	#if __cplusplus > 201703L
	using utString = std::string_view;
	#else
	using utString = std::string;
	#endif
}

#endif