/* 
 * This program kills itself by raising a signal.
 * It's purpose is to test the proper exit status
 * decoding in your shell.
 *
 * Usage: signal signal_number
 *
 * It can be compiled all by itself:
 * g++ -o signal signal.cc
 */


#include <signal.h>		// for: raise(), SIG*
#include <iostream>		// for: std::cerr
#include <cstdlib>		// for: EXIT_*


int	main(int argc, const char *argv[])
{
	if (argc == 1) {
		std::cerr << "Usage: signal signal_number\n";
		exit(EXIT_SUCCESS);
	}
	int  signo = atoi(argv[1]);
	if ((0 < signo) && (signo < 64)) {
		raise(signo);
		exit(EXIT_SUCCESS);
	} else {
		std::cerr << "Signal number " <<signo<< " does not exist\n";
		exit(EXIT_FAILURE);
	}
}
