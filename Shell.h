#ifndef	_Shell_h_
#define	_Shell_h_
/** @file Shell.h
 * Definition of class Shell.
 */

#include <iostream>		// std::istream
#include "Sequence.h"	// class Sequence
#include "Token.h"		// class Token


/** @class Shell
 * This class is the main command line interpreter.
 */
class	Shell
{
	private:

		std::istream 	 & input;		// The input stream to be read

		Token			 * tp;			// The current token during parsing

	public:

		/// Construct a shell that will execute commands
		/// entered via the given istream.
		/// @param input	The input stream to read
		Shell(std::istream& input);		// initialize

		/// The main function of the shell.
		///   It will prompt the user for a command;
		///   Then it calls the internal 'parse()' method
		///   to parse the input line, building a matching
		///   Sequence datastructure;
		///   Then it calls the internal 'execute()' command
		///   to have the commandline executed.
		/// This cycle is repeated until end of input
		/// or some error occurs.
		void	main();

	protected:

		// Note: this section was only made protected
		// 		so doxygen will add it to the documentation

		/// Parses one line of input.
		/// It builds a sequence of pipelines.
		/// @return	The sequence of pipelines to execute
		/// @note This is a, slightly modified,
		///	<a target='info'
		/// href='http://en.wikipedia.org/wiki/Recursive_descent_parser'>recursive-descent parser</a>.
		Sequence	*parse();

		/// Executes the a pipeline-sequence build by 'parse()'.
		/// @param sequence	The sequence of pipelines to execute.
		/// @return	The final exit status of the command.
		void	execute( Sequence *sequence );

		// The LL(1) recursived-descend parser functions
		void	parseSequence(Sequence *sp);
		void	parsePipeline(Pipeline *pp);
		void	parseCommand(Command *cp);
		bool	parseIORedirection(Command *cp);
		void	parseInput(Command *cp);
		void	parseOutput(Command *cp);
		void	parseAppend(Command *cp);

		void	proceed();

		// TODO: Add any other methods you need

};

// vim:ai:aw:ts=4:sw=4:
#endif	/*_Shell_h_*/
