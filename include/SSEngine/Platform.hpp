// _WIN32 indicates both win32 and win64
#ifdef _WIN32 && !_WIN64
#define SS_PLATFORM_WIN32
#endif

#ifdef _WIN64
#define SS_PLATFORM_WIN64
#endif

#ifdef SS_PLATFORM_WIN32 || SS_PLATFORM_WIN64
#define SS_PLATFORM_WIN
#endif

#ifdef __linux__
#define SS_PLATFORM_LINUX
#endif

#ifdef __unix__
#define SS_PLATFORM_UNIX
#endif

#ifdef Macintosh
#define SS_PLATFORM_MAC
#endif

#ifdef __ANDROID__
#define SS_PLATFORM_ANDROID
#define SS_PLATFORM_ANDROID_API __ANDROID_API__
#endif

#ifdef __CYGWIN__
#define SS_PLATFORM_CYGWIN
#endif