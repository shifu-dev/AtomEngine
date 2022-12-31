#pragma once

////////////////////////////////////////////////////////
// CPP STANDARD

#if __cplusplus >= 201103L
#define ATOM_CPP11
#endif

#if __cplusplus >= 201402L
#define ATOM_CPP14
#endif

#if __cplusplus >= 201703L
#define ATOM_CPP17
#endif

#if __cplusplus >= 202002L
#define ATOM_CPP20
#endif

////////////////////////////////////////////////////////
// PLATFORM

// _WIN32 indicates both win32 and win64
#if defined(_WIN32) && !defined(_WIN64)
#define ATOM_PLATFORM_WIN32
#endif

#if defined(_WIN64)
#define ATOM_PLATFORM_WIN64
#endif

#if defined(ATOM_PLATFORM_WIN32) || defined(ATOM_PLATFORM_WIN64)
#define ATOM_PLATFORM_WIN
#endif

#if defined(__linux__)
#define ATOM_PLATFORM_LINUX
#endif

#if defined(__unix__)
#define ATOM_PLATFORM_UNIX
#endif

#if defined(Macintosh)
#define ATOM_PLATFORM_MAC
#endif

#if defined(__ANDROID__)
#define ATOM_PLATFORM_ANDROID
#define ATOM_PLATFORM_ANDROID_API __ANDROID_API__
#endif

#if defined(__CYGWIN__)
#define ATOM_PLATFORM_CYGWIN
#endif

////////////////////////////////////////////////////////

#if defined(ATOM_PLATFORM_WIN)

#if defined(ATOM_BUILD_DLL)
#define ATOM_API __declspec(dllexport)
#else
#define ATOM_API __declspec(dllimport)
#endif

#elif defined(ATOM_PLATFORM_LINUX)

#if defined(ATOM_BUILD_DLL)
#define ATOM_API __attribute__((visibility("default")))
#else
#define ATOM_API
#endif

#else
#error AtomEngine: Unknown Platform.
#endif