#ifndef	_Command_h_
#define	_Command_h_
/** @file Command.h
 * Definition of class Command.
 */

#include <string>	// std::string
#include <vector>	// std::vector

/** @class Command
 * The program to be executed.
 */
class	Command
{
	private:

		// The words that make up the command.
		std::vector<std::string>	words;

		// IO redirection information
		std::string					input;	// name of input file
		std::string					output;	// name of output file
		bool						append;	// use output append mode

	public:

		/// Initialize
		Command();

		/// Add a word to the command
		void	addWord(std::string& word);

		/// Set the name of the standard input file
		/// @pre There may only be one input file specification
		void	setInput(std::string& input);

		/// Set the name of the standard output file
		/// @pre There may only be one output file specification
		void	setOutput(std::string& output);

		/// Set the name of the standard output file in append mode
		/// @pre There may only be one output file specification
		void	setAppend(std::string& output);

		/// Does this command have some input redirection?
		bool	hasInput()	const { return !input.empty(); }

		/// Does this command have some output redirection?
		bool	hasOutput()	const { return !output.empty(); }

		/// Is this an do-nothing-at-all command?
		bool	isEmpty()	const;


		/// Execute the command.
		/// All words are passed to the new process as the program's argument list.
		///
		/// The first word is taken to be the name of the program to be executed.
		/// If the name begins with '/' it is an absolute name.
		/// If the name begins with "./" it is relative to the current directory.
		/// Otherwise it is to be searched for using the PATH environment variable.
		/// (Also see getenv(3), getcwd(3), access(2), execv(3)).
		void	execute();

		// TODO: Add any other methods you need

};

// vim:ai:aw:ts=4:sw=4:
#endif	/*_Command_h_*/
