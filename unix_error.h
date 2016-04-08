#pragma once
#ifndef UNIX_ERROR_H
#define UNIX_ERROR_H 5.1
/** @file unix_error.h
 * Holds the definition of the unix_error exception class
 * thrown when reporting unix errors.
 *
 * @author R.A.Akkersdijk@saxion.nl
 * @version 5.1	2015/11/24
 */

// c++ hooks
#include <stdexcept>	// std::runtime_error
#include <string>		// std::string
#include "where.h"		// The __WHERE__ and __HERE__ macros


/** @class unix_error
 * A class to be used when throwing unix system errors
 * with some additional text (derives from std::runtime_error).
 *
 * When somewhere in your program a systemcall fails,
 * e.g. you can not open a file,
 * the reason is given as a code in the global variable 'errno'.
 *
 * This class takes that code,
 * converting it into some human readable string,
 * addding the given argument as a prefix.
 * <br>Also see: errno, std::strerror() and std::perror()
 *
 * An example:
@code
try {
	// With C++ STL classes
	ifstream  inputfile("some_filename");	// create an ifstream
	if (!inputfile)							// failed to open?
		throw unix_error("inputfile");		// report the problem

	// With unix systemcalls
	if (chdir("/tmp") < 0)					// failed to change directory?
		throw unix_error("chdir /tmp");		// report the problem
} catch(const unix_error& e) {
	cerr << "Oops: " << e.what() << endl;
}
@endcode
 *
 * If you also want to tell <b>where</b> the problem occured
 * you can prepend "__WHERE__" or "__WHERE__" to the message.
@code
try {
	// With C++ STL classes
	ifstream  inputfile("some_filename");	// create an ifstream
	if (!inputfile)							// failed to open?
		throw unix_error(__WHERE__,"inputfile");	// report the problem

	// With unix systemcalls
	if (chdir("/tmp") < 0)					// failed to change directory?
		throw unix_error(__WHERE__,"chdir /tmp");// report the problem
}
@endcode
 */
class unix_error : public std::runtime_error
{
	int			uxerror;	// the unix errno code
public:
	explicit	// see: http://en.cppreference.com/w/cpp/language/explicit
	/// Construct a unix system error with some additional text
	/// @param what	The additional text
	unix_error(const std::string& what);

	explicit	// see: http://en.cppreference.com/w/cpp/language/explicit
	/// Construct a unix system error with some additional text
	/// @param what	The additional text
	unix_error(const char* what);

	/// Construct a unix system error with some additional text
	/// @param where	Where the error occured
	/// @param what		The additional text
	unix_error(const char* where, const char* what);

	/// Construct a unix system error with some additional text
	/// @param where	Where the error occured
	/// @param func		The name of the function where it happened
	/// @param what		The additional text
	unix_error(const char* where, const char* func, const char* what);

	/// Construct a unix system error with some additional text
	/// @param where	Where the error occured
	/// @param func		The name of the function where it happened
	/// @param what		The additional text
	unix_error(const char* where, const char* func, const std::string& what);

	/// Tell the unix errno code
	/// @return the unix errno code
	int		code() const { return uxerror; }
};

// vim:sw=4:ts=4:ai:aw:
#endif // UNIX_ERROR_H
