#include <string>
#include <sstream>	// for: ostringstream
#include "assert_error.h"
using namespace std;


/** @file assert_error.cc
 * This file implements the assert_error exception class.
 *
 * @author R.A.Akkersdijk@saxion.nl
 * @version 4.3	2015/11/24
 */

static
// Some assertion was not met.
// Make a string that informs the user about what is wrong.
string concat3(const char* where, const char *func, const char *what)
{
    if((!func) && (!what))
        return string(where);
    ostringstream ss;
	ss << where;
    if (func)
        ss << " in " << func <<",\n\t";
    ss << what;
    return ss.str();
}

assert_error::assert_error(const char *where, const char *func, const char *what)
    : logic_error( concat3(where,func,what) )
{
}
