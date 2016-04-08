/** @file Pipeline.cc
 * Implementation of class Pipeline.
 */
#include <iostream>
#include <unistd.h>		// for: pipe(), fork(), dup2(), close()
#include "asserts.h"
#include "unix_error.h"
#include "Pipeline.h"
using namespace std;


Pipeline::Pipeline()
	: background(false)
{
}


void	Pipeline::addCommand(Command *cp)
{
	require(cp != 0);
	commands.push_back(cp);
}


Pipeline::~Pipeline()
{
	for (vector<Command*>::iterator  i = commands.begin() ; i != commands.end() ; ++i)
		delete  *i;
}


bool	Pipeline::isEmpty()	const
{
	return commands.empty();
}


// Execute the commands in this pipeline in parallel
void	Pipeline::execute()
{
	//cerr << "Pipeline::execute\n";//DEBUG

	// Because we want the shell to wait on the rightmost process only
	// we must created the various child processes from the right to the left.
	// Also see: pipe(2), fork(2), dup2(2), dup(2), close(2), open(2).
	// And maybe usefull for debugging: getpid(2), getppid(2).
	size_t	 j = commands.size();		// for count-down
	// TODO
	for (vector<Command*>::reverse_iterator  i = commands.rbegin() ; i != commands.rend() ; ++i, --j)
	{
		Command  *cp = *i;
		if (j == commands.size()) {//DEBUG
			///cerr << "Pipeline::RIGHTMOST PROCESS\n";//DEBUG
		}//DEBUG
		//TODO
		cp->execute();
		if (j == 1) {//DEBUG
			///cerr << "Pipeline::LEFTMOST PROCESS\n";//DEBUG
		} else {//DEBUG
			///cerr << "Pipeline::CONNECT TO PROCESS\n";//DEBUG
		}//DEBUG
	}
}

// vim:ai:aw:ts=4:sw=4:
