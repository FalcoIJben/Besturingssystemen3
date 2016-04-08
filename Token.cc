// vim:sw=4:ai:aw:ts=4:
/** @file
 * Implementation of the Token class.
 */
//
//static char sccsid[] = "@(#)Token.cc	2.1	AKK - 20121130";
//

#include "asserts.h"

#include "Token.h"

#include <cctype>	// C: character typing
#include <cstring>	// C: string functions


// The complexity level of tokens recognized
Token::Level  Token::level = Token::BASH;	// highest level


// Function to set the desired token level
void	Token::setLevel(Level new_level)
{
	require( (Token::BASIC <= new_level) && (new_level <= Token::BASH) );
	level = new_level;
}


// ========================================================
// Om conflicten met namen in de rest van het programma te
// vermijden zijn heel veel dingen "static" gemaakt, m.a.w.
// ze zijn alleen zichtbaar in deze source file.
// ========================================================


static
inline	// Is C a whitespace character ?
bool	isBlank(char c) { return ((c == ' ') | (c == '\t')); }


static
// The list of all characters that terminate a "word"
// which depends on the set of tokens recognized.
const char	*specials[4] = 
{
	"\n\r&;|<> \t",			// 0: basic
	"\n\r()&;|<>$ \t",		// 1: advanced
	"\n\r(){}&;|<>$` \t",	// 2: sh-script
	"\n\r(){}&;|<>$` \t",	// 3: bash/ksh-script
};


static
// Does C occur in the list of special characters ?
bool	isSpecial(Token::Level level, char c)
{
	return (strchr(specials[level], c) != 0);
}

static
// The mnemonics for the token types
// (WARNING: must stay in sync with the token_t enum !)
const char *tNames[] =
{
	// == basic ==
	"END",
	"EOL",
	"SEQUENCE",
	"PIPE",
	"INPUT",
	"OUTPUT",
	"APPEND",
	"BACKGROUND",
	// == advanced level ==
	"AND",
	"OR",
	"SUBS",
	"ENDS",
	"VAR",
	"EXPR",
	// == sh level ==
	"HERE",
	"BQUOTE",
	"BREAK",
	"GROUP",
	"GRPEND",
	// == ksh/bash level ==
	"EVAL",
	"WORD"
};


// The global scanner function.
// Note: The "if (!is.get(c)) ..." construct used below
// 	 	 is needed to handle "unexpected EOF" situations.
Token	 *Token::nextToken(istream& is)
{
	string  s;
	char    c = -1;

	// Worth the trouble doing anything ?
	if (!is)
		return new Token(Token::END);

	// Get one character (if possible)
	if (!is.get(c))
		return new Token(Token::END);

	// Skip any white space ...
	while (isBlank(c)) {
		if (!is.get(c))
			return new Token(Token::END);
	}

	// What have we got now ?

	switch(c) {	// First look for special cases

	case '\n': case '\r':
		return new Token(Token::EOL);

	case ';':	// Can be either ; or ;;
		if (Token::level >= Token::SH) {	// iff sh-script: could be ;;
			if (!is.get(c))	// lookahead
				return new Token(Token::SEQUENCE);
			if (c == ';')
				return new Token(Token::BREAK);
			is.putback(c);	// undo lookahead
		}
		return new Token(Token::SEQUENCE);

	case '&':	// Can be either & or &&
		if (Token::level > Token::BASIC) {	// iff advanced: could be &&
			if (!is.get(c))	// lookahead
				return new Token(Token::BACKGROUND);
			if (c == '&')
				return new Token(Token::AND);
			is.putback(c);	// undo lookahead
		}
		return new Token(Token::BACKGROUND);

	case '|':	// Can be either | or ||
		if (Token::level > Token::BASIC) {	// if advanced: could be ||
			if (!is.get(c))	// lookahead
				return new Token(Token::PIPE);
			if (c == '|')
				return new Token(Token::OR);
			is.putback(c);	// undo lookahead
		}
		return new Token(Token::PIPE);

	case '>':	// Can be either > or >>
		if (!is.get(c))	// lookahead
			return new Token(Token::OUTPUT);
		if (c == '>')
			return new Token(Token::APPEND);
		is.putback(c);	// undo lookahead
		return new Token(Token::OUTPUT);

	case '<':	// Can be either < or <<
		if (Token::level >= Token::SH) {	// if sh-scripts: could be <<
			if (!is.get(c))	// lookahead
				return new Token(Token::INPUT);
			if (c == '<')
				return new Token(Token::HERE);
			is.putback(c);	// undo lookahead
		}
		return new Token(Token::INPUT);

	case '(':	// subshell begin
		if (Token::level == Token::BASIC)	// must at least be advanced level
			break;		// treat like ordinary char
		return new Token(Token::SUBS);

	case ')':	// subshell end
		if (Token::level == Token::BASIC)	// must at least be advanced level
			break;		// treat like ordinary char
		return new Token(Token::ENDS);

	case '$':	// variables: $something
		if (Token::level == Token::BASIC)	// must at least be advanced level
			break;		// treat like ordinary char
		if (!is.get(c))	// lookahead
			return new Token(Token::WORD, "");	// just a $ ?
		if (Token::level >= Token::BASH) {	// bash/ksh ?
			// The $( pair is not a variable
			if (c == '(')
				return new Token(Token::EVAL);
		}
		// The following non-letter pairs are common
		//     $* $@ $# $0 ... $9 $? $! $$
		if (strchr("*@#0123456789?!$", c) != NULL) {
			s += c;
			return new Token(Token::VAR, s);
		}
		// Having handled all the special cases,
		// we now expect a true word (e.g. $PATH)
		// which MUST begin with a letter.
		if (!isalpha(c)) {
			is.putback(c);			// Can not use this one
			return new Token(Token::WORD, "");	// just a $ ?
		}
		// Oke, this looks promissing ...
		// Collect an alfanumeric string (a _ also counts as a letter)
		do {
			s += c;
			if(!is.get(c))
				return new Token(Token::VAR, s);
		} while (isalnum(c) || (c == '_'));
		is.putback(c);	// undo lookahead
		return new Token(Token::VAR, s);

	case '{':	// sh-script ? group begin
		if (!(Token::level >= Token::SH))
			break;		// treat like ordinary char
		return new Token(Token::GROUP);

	case '}':	// sh-script ? group end
		if (!(Token::level >= Token::SH))
			break;		// treat like ordinary char
		return new Token(Token::GRPEND);

	case '`':	// sh-script? (back-quotes)
		if (!(Token::level >= Token::SH))
			break;		// treat like ordinary char
		return new Token(Token::BQUOTE);

	} // end special character switch

	// Assume it is just a word;
	// Read any text upto something special.
	Token::token_t  type = Token::WORD;

	do {
		s += c;
		if (!is.get(c))
			return new Token(type, s);
		if (Token::level > Token::BASIC) {	// advanced ?
			// An embedded (simple) wildcard character ?
			// MAYBE: Handle [...] as well
			if (strchr("*?", c) != NULL)	// yes
				type = Token::EXPR;			// change type from WORD to EXPR
		}
	} while (!isSpecial(Token::level, c));
	is.putback(c);	// undo lookahead

	return new Token(type, s);
}


// The output operator for tokens
ostream&  operator<<(ostream& os, const Token& t)
{
	os << "Token: type="<<t.type << " ("<<tNames[t.type]<<")";
	switch (t.type) {	// with text ?
		case Token::VAR:
		case Token::EXPR:
		case Token::WORD:
			os << " '"<<t.text<<"'";
		default:
			break;
	}
	return os;
}
