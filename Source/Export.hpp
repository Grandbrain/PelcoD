/// \file Export.hpp
/// \brief Contains macro definitions that provide directives to export types
/// from shared library.
/// \bug No known bugs.

#ifndef EXPORT_HPP
#define EXPORT_HPP

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
	#define SHARED_IMPORT __declspec(dllimport)
	#define SHARED_EXPORT __declspec(dllexport)
	#define SHARED_LOCAL
#else
	#if __GNUC__ >= 4
		#define SHARED_IMPORT __attribute__ ((visibility ("default")))
		#define SHARED_EXPORT __attribute__ ((visibility ("default")))
		#define SHARED_LOCAL  __attribute__ ((visibility ("hidden")))
	#else
		#define SHARED_IMPORT
        #define SHARED_EXPORT
        #define SHARED_LOCAL
	#endif
#endif

#if defined(PELCOD_LIBRARY)
	#define SHARED_API SHARED_EXPORT
#else
	#define SHARED_API SHARED_IMPORT
#endif

#endif
