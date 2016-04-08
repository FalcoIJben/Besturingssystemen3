#ifndef	ASSERTS_H
#define	ASSERTS_H 5.2
/** @file asserts.h
 * This file defines various macro's that can be used as checks in your program.
 * <br>Note: If NDEBUG has been defined the assertions will be totally disabled for that
 * translation unit.
 *
 * @author R.A.Akkersdijk@saxion.nl
 * @version 5.2	2016/01/19
 */

// First remove these macro's
#undef	require
#undef	check
#undef	ensure
#undef	notreached


#ifdef	NDEBUG		/* === disable asserts? === */


// Make sure that another #include "asserts.h" can be used
// to enable assertions again later.
# undef ASSERTS_H

// Define some dummy macro's that have no side-effects
// and will be eliminated by the compiler
# define require(expr)	((void)(0))
# define check(expr)	((void)(0))
# define ensure(expr)	((void)(0))
# define notreached()	((void)(0))


#else				/* === asserts enabled === */


# include "where.h"			// the filename[linenumber] C-string and the function name
# include "assert_error.h"	// the assert_error class


// What to do if an assertion is not true
# define	ASSERTFAILED(what)\
	throw assert_error(__WHERE__," " what " failed")


/**
 * Verify whether a \c precondition is met, for instance: require(x>0);
 * This will typically be used at the beginning of a function or method.
 */
# define	require(condition) \
	do { if(!(condition)) ASSERTFAILED("require "#condition); } while(0)

/**
 * Verify an internal \c consistenty \c check, for instance: check(x>0);
 * This will typically be used somewhere in a function or method.
 */
# define	check(condition) \
	do { if(!(condition)) ASSERTFAILED("check "#condition); } while(0)

/**
 * Verify whether a \c postcondition is met, for instance: ensure(x>0);
 * This will typically be used at the end of a function or method.
 */
# define	ensure(condition) \
	do { if(!(condition)) ASSERTFAILED("ensure "#condition); } while(0)

/**
 * Verify that this line of code is not reached. For instance
 * when the 'default' case of a 'switch' should never be reached
 * you could say:
 * 		default: notreached();
 * This will typically be used somewhere in a function or method.
 */
# define	notreached() \
	do { ASSERTFAILED("notreached"); } while(0)

#endif			/* === not NDEBUG === */

// vim:sw=4:ai:aw:ts=4:
#endif	/*ASSERTS_H*/
