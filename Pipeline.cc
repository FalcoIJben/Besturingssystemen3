/** @file Pipeline.cc
 * Implementation of class Pipeline.
 */
#include <iostream>
#include <unistd.h>		// for: pipe(), fork(), dup2(), close()
#include "asserts.h"
#include "unix_error.h"
#include "Pipeline.h"
#include <wait.h>
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
	//int  p[j];			// room for the pipe descriptors
    //pipe(p);


	// TODO
	int  p[2];			// room for the pipe descriptors
    pipe(p);
	int cid = fork();


	for (vector<Command*>::reverse_iterator  i = commands.rbegin() ; i != commands.rend() ; ++i, --j)
	{
		Command  *cp = *i;
		//cid = fork();
		if (j == commands.size()) {
            if(cid > 0) {
                int  status = 0;
                int  cid = wait( & status );
                if(status != 0) {
                    cout << "exitstatus of pipeline is not 0" << endl;
                    if(status != 0) {
                        cout << "signal interupted, status: " << status << endl;
                        raise (SIGABRT);
                        cout << "core dumped" << endl;
                    }
                    exit(status);
                }
                if(commands.size() != 1){
                    dup2(p[0], 0);
                }
                dup(1);
                close(p[0]);
                close(p[1]);
                cp->execute();
            }
			///cerr << "Pipeline::RIGHTMOST PROCESS\n";//DEBUG
		}

        if(cid == 0 && j != commands.size()) {
            if(j != 1){
                dup2(p[0], 0);
            }
            dup2(p[1], 1);
            close(p[0]);

            close(p[1]);
            cp->execute();
        }
		if (j == 1) {
            if(cid == 0) {

                exit(EXIT_SUCCESS);
            }
		} else {

		}
	}
}
