/** @file Command.cc
 * Implementation of class Command.
 */
#include <iostream>
#include <fstream>
#include <cstdlib>		// for: getenv()
#include <unistd.h>		// for: getcwd(), close(), execv(), access()
#include <limits.h>		// for: PATH_MAX
#include <fcntl.h>		// for: O_RDONLY, O_CREAT, O_WRONLY, O_APPEND
#include "asserts.h"
#include "unix_error.h"
#include "Command.h"
#include <wait.h>
using namespace std;


// Iff PATH_MAX is not defined in limits.h
#ifndef	PATH_MAX
# define	PATH_MAX (4096)	/* i.e. virtual pagesize */
#endif


Command::Command()
	: append(false)
{
}


void	Command::addWord(string& word)
{
	words.push_back(word);
}


void	Command::setInput(std::string& the_input)
{
	require(input.empty());		// catch multiple inputs
	input = the_input;
}

void	Command::setOutput(std::string& the_output)
{
	require(output.empty());	// catch multiple outputs
	output = the_output;
	append = false;
}

void	Command::setAppend(std::string& the_output)
{
	require(output.empty());	// catch multiple outputs
	output = the_output;
	append = true;
}

// A true "no-nothing" command?
bool	Command::isEmpty() const
{
	return input.empty() && output.empty() && words.empty();
}


// ===========================================================


// Execute a command
void	Command::execute()
{
	// TODO:	Handle I/O redirections.
	//			Don't blindly assume the open systemcall will always succeed!
	// TODO:	Convert the words vector<string> to: array of (char*) as expected by 'execv'.
	//			Note: In this case it safe to typecast from 'const char*' to 'char *'.
	//			Note: Make sure the last element of that array will be a 0 pointer!
	// TODO:	Determine the path of the program to be executed.
	// 			If the name contains a '/' it already is a path name,
	//				either absolute like "/bin/ls" or relative to the
	//				current directory like "sub/prog".
	// 			Otherwise it is the name of an executable file to be
	// 				searched for using the PATH environment variable.
	// TODO:	Execute the program passing the arguments array.
	// Also see: close(2), open(2), getcwd(3), getenv(3), access(2), execv(2), exit(2)

	// TODO: replace the code below with something that really works











    /// commands naar array zetten
    const char *programname = words[0].c_str();

    const char **argv = new const char* [words.size()+2];   // extra room for program name and sentinel
    argv [0] = programname;         // by convention, argv[0] is program name
        for (int j = 1;  j < words.size()+1;  ++j)     // copy args
            argv [j] = words[j] .c_str();

    argv [words.size()] = NULL;  // end of arguments sentinel is NULL

    ///path

    setenv("PWD", getenv("HOME"), 1);
    chdir(getenv("PWD"));
    //cerr << getenv("PWD") << "> " << endl;



    //chdir(getenv("HOME"));
    //cerr << "pwd: "<< getenv("PWD") << endl;
    //cerr << "path: "<< getenv("PATH") << endl;
    //cerr << "display: "<< getenv("DISPLAY") << endl;
    //cerr << "term: "<< getenv("TERM") << endl;
    //cerr << "shell: "<< getenv("SHELL") << endl;






    ///voer programma uit
    int cid = fork(); ///maak nieuw process

    if (cid == 0) {
        ///nieuwe process
        chdir(getenv("PWD"));

        ///I/O
        //cerr << "other input: "<< dup(0) << endl;
        int inf = -1;
        int onf = -1;
        if (!input.empty()) {
            inf = open(input.c_str(), O_RDONLY);
            dup2(inf, 0);
            //cerr << "input: "<< inf << endl;

        }
        //sclose(inf);

        if (!output.empty()) {
            if (append) {
                //cerr << " >>"<< output;
                onf = open(output.c_str(), O_WRONLY| O_CREAT | O_APPEND);
            } else {
                //cerr << " >"<< output;
                onf = open(output.c_str(), O_WRONLY | O_CREAT | O_TRUNC);
            }
            dup2(onf,1);

        }
        close(onf);


        //cerr << "before" << endl;
        int result = execvp (programname, (char **)argv);


        cerr << "failure" << endl;
        exit(EXIT_FAILURE);




    } else {

        /// het orginele process
        int  status = 0;  // Note: only 2 bytes used!
        int  cid = wait( & status );
        exit(status);

        //cerr << "status = " << status << endl; ///????


        //EXIT_SUCCESS;
        //cerr << "ok" << endl;
        //execlp( programname,   "more", 0  );
    }





#if 0	/* DEBUG code: Set to 0 to turn off the next block of code */
	cerr <<"Command::execute ";
	// Show the I/O redirections first ...
	if (!input.empty())
		cerr << " <"<< input;
	if (!output.empty()) {
		if (append)
			cerr << " >>"<< output;
		else
			cerr << " >"<< output;
	}
	// ... now show the command & parameters to execute
	if (words.empty())
		cerr << "\t(EMPTY_COMMAND)" << endl;
	else {
		cerr << "\t";
		for (vector<string>::iterator  i = words.begin() ; i != words.end() ; ++i)
			cerr << " " << *i;
		cerr << endl;
	}
#endif	/* end DEBUG code */
}
