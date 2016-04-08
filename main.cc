/** @file main.cc
 * The main program that creates a Shell instance
 * and then calls it's main method.
 * It also catches any exceptions thrown.
 */
using namespace std;
#include <stdexcept>	// std::exception
#include <iostream>		// std::cin, std::cerr
#include <cstdlib>		// EXIT_SUCCESS, EXIT_FAILURE

#include "ansi.h"		// ansi color code strings (AC_RED, AA_RESET)
#include "assert_error.h"
#include "unix_error.h"

#include "Shell.h"


int	main()
{
	try {
		Shell  shell(cin);	// A shell instance reading commands from cin
		shell.main();		// Do it
		return EXIT_SUCCESS;
	} catch(const unix_error& e) {
		cerr << AC_RED << e.what() << AA_RESET << endl;
		return e.code();
	} catch(const assert_error& e) {
		cerr << AC_RED << e.what() << AA_RESET << endl;
		return EXIT_FAILURE;
	} catch(const exception& e) {
		cerr << AC_RED "Exception: " AA_RESET << e.what() << endl;
		return EXIT_FAILURE;
	} catch(...) {
		cerr << AC_RED "OOPS: something went wrong" AA_RESET << endl;
		return EXIT_FAILURE;
	}
}
