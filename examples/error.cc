/* 
 * This program exits with a given error code.
 * It's purpose is to test the proper exit status
 * decoding in your shell.
 *
 * Usage: error error_number
 *
 * It can be compiled all by itself:
 * g++ -o error error.cc
 */


#include <iostream>		// for: std::cerr
//#include <cerrno>		// for: errno, ...
#include <cstdio>		// for: sys_nerr, ...
#include <cstdlib>		// for: EXIT_*


int	main(int argc, const char *argv[])
{
	if (argc == 1) {
		std::cerr << "Usage: error error_number\n";
		exit(EXIT_SUCCESS);
	}
	int  error_code = atoi(argv[1]);
	if ((0 < error_code) && (error_code <= sys_nerr)) {
		exit(error_code);
	} else {
		std::cerr << "Error number " <<error_code<< " does not exist\n";
		exit(EXIT_FAILURE);
	}
}
