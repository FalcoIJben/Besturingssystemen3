/** @file Shell.cc
 * Implementation of class Shell.
 */
#include <signal.h>		// for: signal, SIG*
#include "asserts.h"
#include "syntax_error.h"
#include "Shell.h"
#include "Token.h"
using namespace std;

// =============================================================================
// INITIALIZE

// Initialize a Shell instance
Shell::Shell(istream& input)
	: input(input), tp(0)
{
	// Select the set of tokens to be recognized
	Token::setLevel( Token::BASIC );
}

// =============================================================================
// MAIN CYCLE

// The main level function
void	Shell::main()
{
	// Ignore some signals
	// TODO:
	// but never these ones
	// TODO:


	// The command loop
	do {
		cout << "SHELL: " << flush;				// prompt the user for command
		Sequence  *sequence = parse();			// parse one line of input
		// syntax sanity check
		if ( (tp->getType() != Token::EOL)		// expect either an EOL
		  && (tp->getType() != Token::END) )	// or end-of-input
			throw syntax_error("Expected EOL got " + tp->getText() );
		if (!sequence->isEmpty())				// anything to do?
			execute( sequence );				// oke, execute it
		delete sequence;						// discard the sequence
	} while (tp->getType() == Token::EOL);		// while more input expected
	cout << "GOODBYE\n";
}

// =============================================================================
// PARSER SUPPORT

// Delete the current token
// and read the next one
void	Shell::proceed()
{
	if (tp)							// some old token?
		delete tp;					// discard it.
	tp = Token::nextToken(input);	// get a new one
	//cerr << *tp << endl;			//DEBUG
}

// =============================================================================
// PARSER

// Parse a single line of input
// returning the sequence of pipelines created.
Sequence	*Shell::parse()
{
	//cerr << "Shell::parse\n";	//DEBUG
	proceed();							// get the first input token
	Sequence  *sp = new Sequence;
	parseSequence(sp);					// read a commandline
	return sp;
}


// Try to parse a sequence ... e.g. abc ; def ; ghi
void	Shell::parseSequence(Sequence *sp)
{
	//cerr << "Shell::parseSequence\n";	//DEBUG
	Pipeline  *pp = new Pipeline;
	parsePipeline(pp);					// read a pipeline
	if (pp->isEmpty()) {
		delete pp;
		pp = 0;
	}
	else
		sp->addPipeline(pp);

	// More to do ?
	//cerr << "Shell::parseSequence more?\n";	//DEBUG
	while ( (tp->getType() == Token::SEQUENCE)		// a ';' ?
		 || (tp->getType() == Token::BACKGROUND) )	// or a '&' ?
	{
		// Do we have to set background mode for the previous pipeline?
		if ((pp) && (tp->getType() == Token::BACKGROUND))
			pp->setBackground();
		proceed();								// oke, discard the ';' or '&'
		pp = new Pipeline();
		parsePipeline(pp);						// read a pipeline
		if (pp->isEmpty()) {
			delete pp;
			pp = 0;
		} else
			sp->addPipeline(pp);
	}
}


// Try to parse a pipeline ... e.g. abc | def | ghi
void	Shell::parsePipeline(Pipeline *pp)
{
	//cerr << "Shell::parsePipeline\n";	//DEBUG
	Command  *cp = new Command;
	parseCommand(cp);				// read a command
	if (cp->isEmpty()) {
		delete cp;
		cp = 0;
	} else
		pp->addCommand(cp);

	// More to do ?
	//cerr << "Shell::parsePipeline more?\n";	//DEBUG
	while (tp->getType() == Token::PIPE) {	// a '|' ?
		proceed();							// oke, discard the '|'
		cp = new Command;
		parseCommand(cp);					// read a command
		if (cp->isEmpty()) {
			delete cp;
			cp = 0;
		} else
			pp->addCommand(cp);
	}
}


// Try to parse a command ... e.g. word word word
void	Shell::parseCommand(Command *cp)
{
	//cerr << "Shell::parseCommand\n";	//DEBUG
	// A command is a sequence of words ...
	do {
		//cerr << "Shell::Command getWord\n";	//DEBUG
		while (tp->getType() == Token::WORD) {
			cp->addWord( tp->getText() );
			proceed();							// oke
		}
		// ... possibly interspersed with io-redirections
	} while (parseIORedirection(cp));
}


// Iff an IO-redirection is found,
// add it to the given Command
// @return true iff an io-redirection was found
bool	Shell::parseIORedirection(Command *cp)
{
	//cerr << "Shell::parseIORedirection\n";	//DEBUG
	// Examine the current token
	switch (tp->getType())
	{
		case Token::INPUT:	// the < symbol
			proceed();		// discard <
			parseInput(cp);
			return true;

		case Token::OUTPUT:	// the > symbol
			proceed();		// discard >
			parseOutput(cp);
			return true;

		case Token::APPEND:	// the >> symbol
			proceed();		// discard >>
			parseAppend(cp);
			return true;

		default:
			break;
	}
	return false;
}

// Parse an < IO-redirection
void	Shell::parseInput(Command *cp)
{
	//cerr << "Shell::parseInput\n";	//DEBUG
	if (tp->getType() == Token::WORD) {
		cp->setInput( tp->getText() );
		proceed();
	} else
		throw syntax_error("Expect a word after <, got " + tp->getText() );
}

// Parse an > IO-redirection
void	Shell::parseOutput(Command *cp)
{
	//cerr << "Shell::parseOutput\n";	//DEBUG
	if (tp->getType() == Token::WORD) {
		cp->setOutput(tp->getText());
		proceed();
	} else
		throw syntax_error("Expect a word after >, got " + tp->getText() );
}

// Parse an >> IO-redirection
void	Shell::parseAppend(Command *cp)
{
	//cerr << "Shell::parseAppend\n";	//DEBUG
	if (tp->getType() == Token::WORD) {
		cp->setAppend(tp->getText());
		proceed();
	} else
		throw syntax_error("Expect a word after >>, got " + tp->getText() );
}


// =============================================================================
// EXECUTE

void	Shell::execute( Sequence *sequence )
{
	//cerr << "Shell::execute\n";	//DEBUG
	require(sequence != 0);
	if (!sequence->isEmpty()) {			// anything to do?
		sequence->execute();			// delegate the work
	}
}

// vim:ai:aw:ts=4:sw=4:

