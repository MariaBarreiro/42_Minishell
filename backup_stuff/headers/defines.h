#ifndef DEFINES_H
#define DEFINES_H

/*
	Lexical layer.
	The enum classifies the kinds of tokens possible
		that the lexer can find.
*/

typedef enum e_token_type
{
    T_WORD,					//normal word like "ls"
    T_PIPE,					// | 
    T_REDIR_IN,				// <
    T_REDIR_OUT,			// >
    T_REDIR_APPEND,			// >>
    T_HEREDOC,				// <<
} t_token_type;

#endif
