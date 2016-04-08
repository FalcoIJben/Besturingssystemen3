#ifndef	__WHERE__
/** @file where.h
 * This file defines the \__WHERE__ and \__HERE__ macros.
 * \__HERE__ produces a filename[linenumer] string constant.
 * \__WHERE__ also adds the function name.
 
 * @author R.A.Akkersdijk@saxion.nl
 * @version 5.2	2016/01/19
 */

// Need some fancy pre-processor magic here
#define NUMBER2STRING2(x)#x
#define NUMBER2STRING(x)NUMBER2STRING2(x)

/// A macro to generate a <tt style='color:green'>"filename[linenumber]"</tt> C-string.
#define __HERE__ __FILE__ "[" NUMBER2STRING(__LINE__) "]"

/// A macro to generate the compound:
/// 	<tt style='color:green'>"filename[linenumber]", "functionname"</tt>
/// to be used in a PARAMETER list!
#ifdef __GNUC__	/* Can we use this extension ? */
#define	__WHERE__ __HERE__,__PRETTY_FUNCTION__
#else			/* No, use the standard macro */
#define	__WHERE__ __HERE__,__func__
#endif
# endif	/*WHERE*/
