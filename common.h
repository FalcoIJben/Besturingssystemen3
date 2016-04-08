#pragma once
#ifndef COMMON_H
#define COMMON_H
/** @file common.h
 *	@brief platform stuff
 *
 * This file contains platform and compiler dependent
 * definitions that are used in various places.
 * When included make sure it is the first \#include line.
 *
 * Current tokens:
 * <dl>
 *   <dt>\__ECLIPSE__
 *   <dd>Set this to 1 when using eclipse as your ide.
 *   <dt>\__DEVCPP__
 *   <dd>Set this to 1 when using DevCPP as your ide.
 * </dl>
 */


// A few handcrafted capabilities ...

// Some IDEs need special treatment (set to 1 as needed)

// Als je Eclipse gebruikt maak van de 0 een 1
#define	__ECLIPSE__	0	///< Eclipse will not handle ansi color codes.

// Als je DevCPP gebruikt maak van de 0 een 1
#define	__DEVCPP__	0	///< When using DevCPP your program window disappears immediately.


// MacOS fails to define __unix__
#if !defined(__unix__) && defined(__APPLE__)
	// maybe also look for __clang__ ?
#  define __unix__ 1
#endif


// Try to detect the platform and compiler (the outcome is not really used yet)
#if   defined(__MINGW_H)	/* is this the "Minimalist GNU for Windows" compiler */
	// Also: __MINGW32__ and __MINGW64__
// this could be Code::Blocks or DevC++; not be further autodetected
#elif   defined(__CYGWIN__)	/* is this Cygnus for Windows ? */
#elif  	defined(__linux__)	/* is this compiled on a linux machine ? */
// this could be Code::Blocks, Eclipse or plain GCC; not be further autodetected
#elif   defined(_WIN32)		/* is this some 32 bit Windows ? */
#elif   defined(_WIN64)		/* is this some 64 bit Windows ? */
#endif


#endif	/*COMMON_H*/

// vim:sw=4:ts=4:ai:aw:

