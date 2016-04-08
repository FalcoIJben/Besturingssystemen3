#pragma once
#ifndef	ANSI_H
#define	ANSI_H 1.2
/** @file ansi.h
 * Defines various ansi color-code strings.
 * See e.g.
 * <a target='info' href='http://en.wikipedia.org/wiki/ANSI_escape_code'>ansi escape code</a>
 * <br>Available are:
 * <br>AS_xxx (set style to: BOLD, UNDERLINE or INVERTED)
 * <br>AC_xxx (set foreground color to: BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN or WHITE)
 * <br>AB_xxx (set background color to: BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN or WHITE)
 * <br>AA_RESET (reset to normal)
 *
 * @note
 * If the \__ECLIPSE__ pre-processor token was defined
 * the strings will be left empty because the eclipse
 * console will not handle ansi color-codes.
 *
 * @note
 * If this file is used on a non-unix platform
 * the strings will be left empty because
 * it is unlikely that that platform (e.g. windows)
 * will handle ansi codes.
 *
 * @author R.A.Akkersdijk@saxion.nl
 * @version 1.2	2012/09/24
 */

#include "common.h"	// for: __ECLIPSE__ check


// Ansi Color Code sequences

#if	defined(__unix__) && !(__ECLIPSE__)

// styles
#define	AS_BOLD			"\33[1m"
#define	AS_UNDERLINE	"\33[4m"
#define	AS_INVERTED		"\33[7m"
// foreground colors
#define	AC_BLACK	"\33[30m"
#define	AC_RED		"\33[31m"
#define	AC_GREEN	"\33[32m"
#define	AC_BROWN	"\33[33m"	// aka yellow
#define	AC_BLUE		"\33[34m"
#define	AC_MAGENTA	"\33[35m"
#define	AC_CYAN		"\33[36m"
#define	AC_WHITE	"\33[37m"
// background colors
#define	AB_BLACK	"\33[40m"
#define	AB_RED		"\33[41m"
#define	AB_GREEN	"\33[42m"
#define	AB_BROWN	"\33[43m"	// aka yellow
#define	AB_BLUE		"\33[44m"
#define	AB_MAGENTA	"\33[45m"
#define	AB_CYAN		"\33[46m"
#define	AB_WHITE	"\33[47m"
// reset attributes
#define	AA_RESET	"\33[m"


#else /* Windows and Eclipse will not handle ansi codes */


// styles
#define	AS_BOLD			""
#define	AS_UNDERLINE	""
#define	AS_INVERTED		""
// foreground colors
#define	AC_BLACK	""
#define	AC_RED		""
#define	AC_GREEN	""
#define	AC_BROWN	""	// aka yellow
#define	AC_BLUE		""
#define	AC_MAGENTA	""
#define	AC_CYAN		""
#define	AC_WHITE	""
// background colors
#define	AB_BLACK	""
#define	AB_RED		""
#define	AB_GREEN	""
#define	AB_BROWN	""	// aka yellow
#define	AB_BLUE		""
#define	AB_MAGENTA	""
#define	AB_CYAN		""
#define	AB_WHITE	""
// reset attributes
#define	AA_RESET	""

#endif /* windows/eclipse hack */

#endif	/*ANSI_H*/
// vim:sw=4:ts=4:ai:aw:
