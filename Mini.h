#ifndef MINI_H

# define MINI_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# define ERR_FLASH "Error\n"
# define ERR_ARG "Error Arg or Pipe\n"
# define ERR_PIPE "Error Pipe\n"
# define ERR_FORK "Error Fork\n"
# define ERRO_INFILE "No such file or directory\n"
# define ERRO_DUP "Error DUP\n"
# define ERRO_OUFILE "Error outfile\n"
# define ERRO_DOC "Error here doc\n"
# define ERRO_FEW "Few args\n"
# define SYNTAX_ERROR "bash: syntax error near unexpected token `newline'\n"

extern volatile sig_atomic_t	g_status;

typedef struct s_env
{
	char						*name;
	char						*value;
	int							exported;
	struct s_env				*next;
}								t_env;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_RED_IN,
	T_RED_OUT,
	T_RED_APPEND,
	T_HEREDOC,
	T_INFILE,
	T_OUTFILE,
}								t_token_type;

typedef enum e_token_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}								t_token_quote;

typedef enum e_expansion_type
{
	NO_EXPANSION,
	VAR_EXPANSION,
	EXIT_STATUS_EXPANSION
}								t_expansion_type;

typedef struct s_token
{
	char						*value;
	t_token_type				type;
	t_token_quote				quote;
	t_expansion_type			expansion_type;
	struct s_token				*next;
}								t_token;

typedef struct s_tokenizer
{
	char *input; // String completo
	int pos;     // Posición actual
	t_token_type				prev_type;
	int							err;
}								t_tokenizer;

typedef struct s_redir
{
	int							type;
	char						*filename;
	struct s_redir				*next;
}								t_redir;

typedef struct s_command
{
	char						**argv;
	char						*infile;
	char						*outfile;
	int							append;
	int							is_heredoc;
	char						*heredoc_file;
	struct s_command			*next;
	t_redir						*redirs;
}								t_command;

typedef struct s_fd_pipex
{
	int							prev_fd;
	int							count_heredoc;
	int							n_cmds;
	int							builtins;
	pid_t						*pid;
	t_command					*commands;
}								t_pipex;

typedef struct s_minishell
{
	t_env						*env_list;
	t_token						*token_list;
	t_command					*command_list;
	t_pipex						*pipex_data;
}	t_minishell;

typedef enum e_builtin_type
{
	NO_BUITIN = -1,
	BUILTIN_CHILD = 0,
	BUILTIN_PARENT = 1
}								t_builtin_type;

// signals
int								get_heredoc(char *limiter, char **my_env);
void							do_signal(void);
void							sighandler(int signal);

// Parse
t_command						*parse_single_command(t_token *tokens);
void							free_commands(t_command *cmd);
int								check_syntax_pipes(t_token *tok);

// Tokens
t_token							*create_token_and_detect_expansion(t_token **list,
									char *val, t_token_type type,
									t_token_quote quote);
t_token							*add_token(t_token **head, char *value,
									t_token_type type, t_token_quote quote);
char							*extract_word(t_tokenizer *tok,
									t_token_type *type);
void							free_tokens(t_token *head);
int								fill_tokens(t_token **token_list, char *input);
int								extract_metachar(t_tokenizer *tok,
									t_token_type *type, t_token_quote *quote);
char							*extract_quoted_token(t_tokenizer *tok,
									t_token_type *type, t_token_quote *quote);
char							*extract_complex_token(t_tokenizer *tok,
									t_token_type *type, t_token_quote *quote);
int								is_empty_token(char *temp);
char							*get_next_token_part(t_tokenizer *tok,
									t_token_type *type,
									t_token_quote *current_quote);
char							*extract_quoted_token(t_tokenizer *tok,
									t_token_type *type, t_token_quote *quote);

// Exec
void	execute_pipeline(t_pipex *data, t_command *cmds, char **envir, t_env **env_list);
void							execute_command(t_pipex *data, char **args,
									char **paths, char **envir);
void							parse_heredoc(t_command *cmd, t_token **token,
									t_pipex *data, int *index);
void							process_token(t_command **curr, t_token **token,
									t_pipex *data, int *index);
void							child_process(t_pipex *data, t_command *cmd,
									int fd[2], char **envir);
char							*extract_token(t_tokenizer *tok,
									t_token_type *type, t_token_quote *quote);
void							add_redir_to_cmd(t_command *cmd, int type,
									const char *filename);
char							*handle_heredoc_in_command(t_command *cmd,
									char *limiter, int index);
void	execute_last_command(t_pipex *data, t_command *curr,
		char **envir, int i, t_env **env_list);
void							process_and_exec(t_pipex *data, t_command *cmd,
									int i, char **envir);
void							add_command_to_list(t_command **head,
									t_command *new_cmd);
void							free_struct(t_pipex *data, char *message, int i,
									int std);
void							free_and_exit(char **args, char **paths,
									int exit_code);
void							exit_with_error(char *message, int exit_code,
									int std);
int								get_heredoc_index(t_token *token,
									t_token *target);
void							parse_red_append(t_command *cmd,
									t_token **token);
void							ft_cmd(t_pipex *data, char **argv,
									char **envir);
char							*create_path(char *possible_path,
									char *command);
void							parse_red_out(t_command *cmd, t_token **token);
t_command						*parse_commands(t_token *token, t_pipex *data);
int								here_doc(char *limiter, const char *filename);
void							init_strucs(t_pipex **data, t_command **cmds);
void							add_arg_to_command(t_command *cmd, char *arg);
void							parse_red_in(t_command *cmd, t_token **token);
char							**cmd_managment(t_pipex *data, char *cmd);
int								count_commands_list(t_command *cmd);
void	ft_execute(t_token *token, char **envir, t_env **env_list);
void							apply_redirections(t_command *cmd);
void							free_command_list(t_command *cmd);
void							redir_heredoc(t_command *cmd);
void							apply_heredoc(t_command *cmd);
char							*find_execpath(char **envir);
void							delete_heredoc_files(int n);
char							**split_command(char *cmd);
void							free_stuct(t_pipex *data);
char							*get_filename(int index);
t_command						*init_new_command(void);
void							ft_freedoom(char **str);
int								is_redir(t_redir *redir);
int								has_redir(t_command *cmd);
int								has_redir_type(t_command *cmd, int type);
void							apply_one_redirection(t_redir *redir);
void							wait_status(t_pipex *data);
int								token_has_pipe(t_token *token);
void							free_redirs(t_redir *redir);
// Var
void							expand_token(t_token *token);

// env
char							*get_env_name(char **env, const char *name);
char							**copy_env(char **env);
char							**append_env_variable(char **env,
									const char *name, const char *value);
void							set_env(char ***env, const char *name,
									const char *value);
t_env	*create_env_list(char **envp);

// Built-ins


int								is_builtin(t_token *token);
int								is_builtin_str(char *str);
void							execute_buitin(t_command *cmd, char ***env, t_env **env_list);


void							execute_buitin_args(char **argv, char ***env);
void							ft_echo(t_command *cmd);
void							ft_pwd(char **argv, char **env);
void							ft_echo_arg(char **argv);
void							ft_env(char **argv, char **env);

int								ft_exit(t_command *cmd);
int								is_numeric(const char *str);

void							ft_export(char **argv, t_env **env_list);
void							add_env_node(t_env **env_list, char *name,
									char *value, int exported);
t_env							*find_env(t_env *env_list, const char *name);
t_env	*create_env_list(char **envp);
int	count_exported(t_env *env);
void	print_sorted_env(t_env *env);
void	print_env_array(t_env **arr, int count);
void	sort_env_array(t_env **arr, int count);
void	add_or_update_env(char *arg, t_env **env_list);


// Freedom
void							free_pipex_data(t_pipex *data);
void							free_command_list(t_command *cmd);
void							free_redir_list(t_redir *redir);
void							free_token_list(t_token *token);
void							free_env_list(t_env	*env);
void							free_minishell(t_minishell *minishell);

#endif
