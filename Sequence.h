#ifndef	_Sequence_h_
#define	_Sequence_h_
/** @file Sequence.h
 * Definition of class Sequence.
 */

#include <vector>		// std::vector
#include "Pipeline.h"


/** @class Sequence
 * A sequence of pipelines that are to be executed one after the other.
 * For instance:
 * @code
     abc ; def ; ghi & jkl ; ....
 * @endcode
 * If the ';' separator is used (e.g. "abc") the shell will wait
 * for the pipeline to finish before proceeding
 * to the next pipeline.
 *
 * If the '&' separator is used,
 * the preceding pipeline (i.e. "ghi")
 * becomes a so called
 * '<a target='info' href='http://en.wikipedia.org/wiki/Background_process'>background</a>'
 * pipeline.
 * The shell will not wait for it's completion
 * but immediately proceed to the next pipeline.
 *
 * Background pipelines run at a lower priority,
 * i.e. will have a higher
 * '<a target='info' href='http://casper.cii.saxion.nl/cgi-bin/man2html?+nice+2'>nice(2)</a>'
 * value (usually +5).
 * Their standard input will be connected to "/dev/null"
 * and they have the INTERRUPT and QUIT signals ignored.
 *
 */
class	Sequence
{
	private:

		// The current sequence of pipelines
		std::vector<Pipeline*>	commands;

	public:

		/// Cleanup
		~Sequence();

		/// Append a Pipeline to the commands vector.
		/// @param pp	The pipeline to add
		void	addPipeline(Pipeline *pp);

		/// Tell whether the commands vector is empty or not
		/// @return true	when there is nothing to execute
		bool	isEmpty()	const;

		/// Executes the pipelines stored in 'commands'.
		void	execute();

		// TODO: Add any other methods you need

};

// vim:ai:aw:ts=4:sw=4:
#endif	/*_Sequence_h_*/
