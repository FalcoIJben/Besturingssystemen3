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


    //const char *path = output.c_str();

    //const char **argv = new const char* [words.size()+1];

    //for (int j = 0;  j < words.size()+1;  ++j)     // copy args
            //argv [j+1] = words[j].c_str();

    //argv [words.size()] = NULL;  // end of arguments sentinel is NULL

    //execv ("/home/falco/School/Jaar_2/Kwartiel_3/BestuuringsSystemen/shell/ok.txt", (char **)argv);


    ifstream inputFile;
    ofstream outputFile;


//    cerr << getcwd() << endl;

    ///get input
    string file = "";
    if (!input.empty()) {
        string line;
        inputFile.open(input);
        while ( getline (inputFile,line) ) {
            file += line += '\n';
        }
        inputFile.close();
    }

    for (int i = 0;  i < words.size();  ++i) {
        string word = words[i];

        ///cat
        if(word == "cat" ) {
            if(input.empty()) {
                for (int j = i+1;  j < words.size();  ++j) {
                    string line;
                    ifstream nextFile;
                    word = words[j];

                    nextFile.open(word);
                    while ( getline (nextFile,line) ) {
                        file += line += '\n';
                    }
                    nextFile.close();
                }
            }
            if (!output.empty()) {
                    if (append) {
                        outputFile.open (output, ios::app | ios::ate);
                    } else {
                        outputFile.open (output);
                    }
                    outputFile << file;
                    outputFile.close();
                } else {
                cerr << file;
            }
            break;
        }

        ///other?

    }










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


// vim:ai:aw:ts=4:sw=4:
