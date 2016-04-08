#ifndef SYNTAX_ERROR_H
#define SYNTAX_ERROR_H 1
/** @file syntax_error.h
 * Exception class syntax_error derived from runtime_error
 */

#include <stdexcept>	// std::exception, std::runtime_error
#include <string>		// std::string

/** @class syntax_error
 * A class to throw syntax errors (derives from runtime_error)
 */
class syntax_error : public std::runtime_error
{
public:
	explicit syntax_error(const std::string& what_arg)
				: runtime_error(what_arg) {}
	explicit syntax_error(const char *what_arg)
				: runtime_error(what_arg) {}
};

#endif // SYNTAX_ERROR_H
