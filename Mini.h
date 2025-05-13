#ifndef MINI_H

# define MINI_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_RED_IN,
	T_RED_OUT,
	T_RED_APPEND,
	T_HEREDOC,
	T_INFILE, // despues de <
	T_OUTFILE // despues de >
}						t_token_type;

typedef enum e_token_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}						t_token_quote;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_token_quote		quote;
	struct s_token		*next;
}						t_token;

typedef struct s_tokenizer
{
	char *input; // String completo
	int pos;     // Posición actual
	t_token_type		prev_type;
	int					err;
}						t_tokenizer;

typedef enum e_expansion_type
{
	NO_EXPANSION,
	TILDE_EXPANSION,
	VAR_EXPANSION,
	EXIT_STATUS_EXPANSION
}						t_expansion_type;

typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					append;
	int					is_heredoc;
	char				*heredoc_file;
	struct s_command	*next;
}						t_command;

// Parse
t_command				*parse_single_command(t_token *tokens);
void					free_commands(t_command *cmd);

// Tokens
void	add_token(t_token **head, char *value, t_token_type type, t_token_quote quote);
char					*extract_word(t_tokenizer *tok, t_token_type *type);
void					free_tokens(t_token *head);
int						fill_tokens(t_token **token_list, char *input);
int						extract_metachar(t_tokenizer *tok, t_token_type *type,
							t_token_quote *quote);
char	*extract_quoted_token(t_tokenizer *tok, t_token_type *type,
		t_token_quote *quote);
char	*extract_complex_token(t_tokenizer *tok,
			t_token_type *type, t_token_quote *quote);
int	is_empty_token(char *temp);
char	*get_next_token_part(t_tokenizer *tok,
				t_token_type *type, t_token_quote *current_quote); 

// Exec
char					*find_in_path(char *cmd, char **envp);
void					check_type(t_token *token, char **envir);
char					*extract_token(t_tokenizer *tok, t_token_type *type,
							t_token_quote *quote);
void					execute_command(t_command *cmd, char **envp);

// Variables
void					expand_token(t_token *token, char **env);
int						is_simple_quotes(char *str);

// void	expand_tilde(t_single_token *token, char **env);

/* void	expand_tilde(t_single_token *token, char **env); */

#endif
