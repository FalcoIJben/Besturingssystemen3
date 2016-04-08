#ifndef	__TOKEN_H__
#define	__TOKEN_H__
/** @file
 * Definition of the Token class.
 */
//#ident	"@(#)Token.h	1.5	AKK - 20060526"
//#ident	"@(#)Token.h	2.1	AKK - 20121130"

#include <string>	// std::string
#include <istream>	// std::istream
using std::string;	// import alleen std::string
using std::istream;	// import alleen std::istream
using std::ostream;	// import alleen std::ostream


/// @class Token
/// Describes a <a target='info'
/// href='http://en.wikipedia.org/wiki/Tokenizing'>token</a> from the input.
/// Which kinds of tokens will be recognized
/// can be choosen with setLevel().
/// By default the most advanced
/// BASH/KSH set is recognized.
class	Token
{
	public:
		/// @enum Level
		/// The constants that determine which tokens
		/// will be recognized by the tokenizer.
		enum	Level
		{
			BASIC,		//!< Basic tokens:
						//!<	;  |  <  >  >>  &
			ADVANCED,	//!< Advanced = BASIC plus:
						//!<	&&  ||  (  )  shell-variables  simple-wildcard
			SH,			//!< Shell scripts = ADVANCED plus:
						//!<	<<  `  ;;  {  }
			BASH		//!< Bash/ksh scripts = SH plus:
						//!<	$(  )
		};

		/// @enum token_t
		/// The different kinds of tokens.
		enum	token_t
		{
				// == basic level ==
			END,		//!<   			end-of-input.
						//!< @note We use END here because the code EOF is a macro
						//!< 		already defined in some other include file.
			EOL,		//!<   end-of-line (either \\n or \\r)
			SEQUENCE,	//!<   ;		e.g. foo ; bar
			PIPE,		//!<   |		e.g. run | in | tandem
			INPUT,		//!<   <		e.g. input < from ...
			OUTPUT,		//!<   >		e.g. output > to ....
			APPEND,		//!<   >>		e.g. output >> after ...
			BACKGROUND,	//!<   &		i.e. don't wait

				// == advanced level ==
			AND,		//!<   &&		in a conditional execution.
			OR,			//!<   ||		in a conditional execution.
			SUBS,		//!<   (		subshell begin, as in: ( ... ; ... )
			ENDS,		//!<   )		subshell end, as in: ( ... ; ... )
			VAR,		//!<   			$word or one of $*  $@  $#  $0...$9  $?  $!  $$
						//!< @note The token-text does NOT contain the $ character.
			EXPR,		//!<   			A simple wildcard containing * or ?
						//!< @note The [...] wildcard is NOT recognized.

				// == sh script level ==
			HERE,		//!<   <<		start of an inline document
			BQUOTE,		//!<   `		as in ` ... `	run a subshell & substitute the output here
			BREAK,		//!<   ;;		as in: case ... in ... ;; ... ;; ... esac
			GROUP,		//!<   {		group begin, as in: { ... ; ... }
			GRPEND,		//!<   }		group end, as in: { ... ; ... }

				// == ksh/bash level ==
			EVAL,		//!<   $( ... )	run a subshell & substitute the output here


			WORD		//!<			anything else.
						//!< @note Special words such as 'exit', 'cd' etc.
						//!<	are NOT handled here,
						//!< 	because their meaning is position dependent.
		};

	private:

	static Level level;		// The current token level, by default BASH level

		// per Token instance attributes
		token_t	type;		// The code for the token type.
		string	text;		// The corresponding text from the input.

		explicit
		Token(token_t t) : type(t) {}
		Token(token_t t, const string &s) : type(t), text(s) {}

	public:

		/// Select which level of tokens will be recognized.
		/// By default it is the most advanced BASH level.
	static void	setLevel(Level);

		/// Returns the current token level.
	static Level	getLevel() { return level; }

		// Per token query functions
		token_t   getType() const	{ return type; }
		string&   getText()			{ return text; }


		/// This static function is the actual scanner
		/// which returns the next token from the input.
		/// @return	a pointer to a new Token instance.
		///		The caller must delete that object
		///		when it is no longer needed.
	static Token	 *nextToken(istream &is);

		/// The output operator for tokens
	friend  ostream& operator<<(ostream& os, const Token& token);
};


/// The output operator for tokens
ostream&  operator<<(ostream& os, const Token& token);

// vim:sw=4:ai:aw:ts=4:
#endif	/*TOKEN_H*/
