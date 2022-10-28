#pragma once

#define SS_NAME SoulSphere
#define SS_ENGINE_NAME SoulSphereEngine
#define SS_ENGINE_SHORT_NAME SSEngine

////////////////////////////////////////////////////////
// CPP STANDARD

#if __cplusplus >= 201103L
#define SS_ENGINE_CPP11
#endif

#if __cplusplus >= 201402L
#define SS_ENGINE_CPP14
#endif

#if __cplusplus >= 201703L
#define SS_ENGINE_CPP17
#endif

#if __cplusplus >= 202002L
#define SS_ENGINE_CPP20
#endif

////////////////////////////////////////////////////////
// PLATFORM

// _WIN32 indicates both win32 and win64
#if defined(_WIN32) && !defined(_WIN64)
#define SS_PLATFORM_WIN32
#endif

#if defined(_WIN64)
#define SS_PLATFORM_WIN64
#endif

#if defined(SS_PLATFORM_WIN32) || defined(SS_PLATFORM_WIN64)
#define SS_PLATFORM_WIN
#endif

#if defined(__linux__)
#define SS_PLATFORM_LINUX
#endif

#if defined(__unix__)
#define SS_PLATFORM_UNIX
#endif

#if defined(Macintosh)
#define SS_PLATFORM_MAC
#endif

#if defined(__ANDROID__)
#define SS_PLATFORM_ANDROID
#define SS_PLATFORM_ANDROID_API __ANDROID_API__
#endif

#ifdef __CYGWIN__
#define SS_PLATFORM_CYGWIN
#endif

////////////////////////////////////////////////////////