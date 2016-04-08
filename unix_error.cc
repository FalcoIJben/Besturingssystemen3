/** @file unix_error.cc
 * The implementation of the unix_error exception class.
 * @version 5.1	2015/11/24
 */

// linux & c++ hooks
#include <cstring>		// extern char *strerror(int errnum);
#include <cerrno>		// extern int errno;
#include <sstream>		// ostringstream

// our own stuff
#include "unix_error.h"	// class unix_error


static // (i.e. only visible in this source file)
// A function to combine the given arguments with the unix error message
// that belongs to the given errornumber into a nice c++ string.
std::string	makeErrorString(const char* where, const char* func, const char* what, int errornumber)
{
	std::ostringstream  s;
	if (where)
		s << where << ' ';
	if (func)
		s << "in "<<func << ", ";
	if (what)
		s << what << ": ";
	else
		s << "errno=" << errornumber << ": ";
	s << strerror(errornumber);
	return  s.str();
}


// Construct a unix system error
unix_error::unix_error(const std::string& what)
	: std::runtime_error( makeErrorString( 0, 0, what.c_str(), errno) ), uxerror(errno)
{
}

// Construct a unix system error
unix_error::unix_error(const char *what)
	: std::runtime_error( makeErrorString( 0, 0, what, errno) ), uxerror(errno)
{
}


// Construct a unix system error
unix_error::unix_error(const char* where, const char *what)
	: std::runtime_error( makeErrorString( where, 0, what, errno) ), uxerror(errno)
{
}

// Construct a unix system error
unix_error::unix_error(const char* where, const char* func, const char* what)
	: std::runtime_error( makeErrorString( where, func, what, errno) ), uxerror(errno)
{
}

// Construct a unix system error
unix_error::unix_error(const char* where, const char* func, const std::string& what)
	: std::runtime_error( makeErrorString( where, func, what.c_str(), errno) ), uxerror(errno)
{
}

// vim:sw=4:ai:aw:ts=4:
