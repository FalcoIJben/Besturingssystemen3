#ifndef	_Pipeline_h_
#define	_Pipeline_h_
/** @file Pipeline.h
 * Definition of class Pipeline.
 */


#include <vector>		// std::vector
#include "Command.h"


/** @class Pipeline
 * A group of commands that are to be executed in parallel interconnected by
 * \"<a target='info' href='http://en.wikipedia.org/wiki/Pipeline_(Unix)'>pipes</a>".
 * For instance:
 * @code
     abc | def | ghi | ... | xyz
 * @endcode
 * The standard output of the first process (i.e. "abc")
 * will be connected to the standard input of the second process (i.e. "def").
 * The standard output of the second process (i.e. "def")
 * will be connected to the standard input of the third process (i.e. "ghi").
 * Etc.
 *
 * The shell waits until the rightmost process (i.e. "xyz") ends.
 * The exit status of a pipeline is the exit status
 * of the rightmost process (i.e. "xyz").
 */
class	Pipeline
{

	private:

		// The commands to be executed in parallel
		// interconnected by pipes.
		std::vector<Command*>	commands;

		// Set to true if this is a background pipeline
		bool					background;

	public:

		/// Initialize
		Pipeline();

		/// Cleanup
		~Pipeline();

		/// Append a Command to the pipeline
		/// @param cp The command to be added
		void	addCommand(Command *cp);

		/// Is the pipeline empty?
		/// @return true when empty
		bool	isEmpty()	const;

		/// Set background mode
		void	setBackground()	{ background = true; }

		/// Is this a background pipeline?
		/// @return true is background
		bool	isBackground()	const { return background; }

		/// Executes all the commands stored in 'commands'.
		/// Subsequent processes will be interconnected to each other
		/// via pipes (See: unix manual: pipe(2))
		void	execute();

		// TODO: Add any other methods you need
};

// vim:ai:aw:ts=4:sw=4:
#endif	/*_Pipeline_h_*/
