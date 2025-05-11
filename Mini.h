#ifndef MINI_H

# define MINI_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# define ERR_FLASH "Error\n"
# define ERR_ARG "Error Arg or Pipe\n"
# define ERR_PIPE "Error Pipe\n"
# define ERR_FORK "Error Fork\n"
# define ERRO_INFILE "No such file or directory\n"
# define ERRO_DUP "Error DUP\n"
# define ERRO_OUFILE "Error outfile\n"
# define ERRO_DOC "Error here doc\n"
# define ERRO_FEW "Few args\n"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_RED_IN,
	T_RED_OUT,
	T_RED_APPEND,
	T_HEREDOC,
	T_INFILE,
	T_OUTFILE
}	t_token_type;

typedef enum e_token_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_token_quote;

typedef enum e_expansion_type
{
	NO_EXPANSION,
	VAR_EXPANSION,
	EXIT_STATUS_EXPANSION
}						t_expansion_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_token_quote		quote;
	t_expansion_type	expansion_type;
	struct s_token		*next;
}						t_token;

typedef struct s_tokenizer
{
	char				*input; // String completo
	int					pos;	// Posición actual
	t_token_type		prev_type;
	int					err;
}						t_tokenizer;

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


typedef struct s_fd_pipex
{
	int			prev_fd;
	int			count_heredoc;
	int			n_cmds;
	pid_t		*pid;
	t_command	*commands;
}	t_pipex;


// Parse
t_command				*parse_single_command(t_token *tokens);
void					free_commands(t_command *cmd);

// Tokens
void					add_token(t_token **head, char *value,
							t_token_type type, t_token_quote quote);
char					*extract_word(t_tokenizer *tok, t_token_type *type);
void					free_tokens(t_token *head);
int						fill_tokens(t_token **token_list, char *input);
int						extract_metachar(t_tokenizer *tok, t_token_type *type,
							t_token_quote *quote);
char					*extract_quoted_token(t_tokenizer *tok,
							t_token_type *type, t_token_quote *quote);

// Exec
void					execute_pipeline(t_pipex *data,
							t_command *cmds, char **envir);
void					execute_command_bonus(t_pipex *data, char **args,
							char **paths, char **envir);
void					parse_heredoc(t_command *cmd, t_token **token,
							t_pipex *data, int *index);
void					process_token(t_command **curr, t_token **token,
							t_pipex *data, int *index);
void					child_process(t_pipex *data, t_command *cmd,
							int fd[2], char **envir);
char					*extract_token(t_tokenizer *tok, t_token_type *type,
							t_token_quote *quote);
void					handle_heredoc_in_command(t_command *cmd, char
							*limiter, int index);
void					execute_last_command(t_pipex *data, t_command *curr,
							char **envir, int i);
void					process_and_exec(t_pipex *data, t_command *cmd,
							int i, char **envir);
void					add_command_to_list(t_command **head,
							t_command *new_cmd);
void					free_struct(t_pipex	*data, char *message,
							int i, int std);
void					free_and_exit(char **args, char **paths, int exit_code);
void					exit_with_error(char *message, int exit_code, int std);
int						get_heredoc_index(t_token *token, t_token *target);
void					parse_red_append(t_command *cmd, t_token **token);
void					ft_cmd(t_pipex *data, char **argv, char **envir);
char					*create_path(char *possible_path, char *command);
void					parse_red_out(t_command *cmd, t_token **token);
t_command				*parse_commands(t_token *token, t_pipex *data);
int						here_doc(char *limiter, const char *filename);
void					init_strucs(t_pipex **data, t_command **cmds);
void					add_arg_to_command(t_command *cmd, char *arg);
void					parse_red_in(t_command *cmd, t_token **token);
char					**cmd_managment(t_pipex *data, char *cmd);
int						count_commands_list(t_command *cmd);
void					pipex(t_token *token, char **envir);
void					apply_redirections(t_command *cmd);
void					free_command_list(t_command *cmd);
void					redir_outfile(t_command *cmd);
void					redir_heredoc(t_command *cmd);
void					apply_heredoc(t_command *cmd);
void					apply_outfile(t_command *cmd);
void					apply_infile(t_command *cmd);
void					redir_infile(t_command *cmd);
char					*find_execpath(char **envir);
void					delete_heredoc_files(int n);
char					**split_command(char *cmd);
void					free_stuct(t_pipex *data);
char					*get_filename(int index);
t_command				*init_new_command(void);
void					ft_freedoom(char **str);

// Variables
void					expand_token(t_token *token, char **env);

// void	expand_tilde(t_single_token *token, char **env);

/* void	expand_tilde(t_single_token *token, char **env); */

#endif
