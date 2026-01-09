#ifndef COMMON_H
#define COMMON_H

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( _WIN64 )
#define PLATFORM_WIN 1
#define PLATFORM_POSIX 0
#else
#define PLATFORM_WIN 0
#define PLATFORM_POSIX 1
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
/* C11 */
#define NORETURN _Noreturn
#elif defined(_MSC_VER)
/* MSVC (pre-C11) */
#define NORETURN __declspec(noreturn)
#elif defined(__GNUC__) || defined(__clang__)
/* GCC/Clang (pre-C11) */
#define NORETURN __attribute__((noreturn))
#else
/* Fallback */
#define NORETURN
#endif

#endif
