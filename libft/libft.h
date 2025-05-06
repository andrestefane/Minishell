/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:05:07 by astefane          #+#    #+#             */
/*   Updated: 2025/05/06 13:27:02 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../Mini.h"
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

struct					s_token;
typedef struct s_token t_token;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Memory

void		free_and_error(char *str, char *message, int exit_code, int std);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		free_split(char **str);

// String Fuctions

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *s1, const char *s2, size_t len);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strtrim(const char *s1, const char *set);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char *s1, const char *s2);
char		*ft_strndup(const char *s, int n);
char		*ft_strrchr(const char *s, int c);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
int			ft_strlen(const char *s);
char		*ft_itoa(int n);

// Mem Fuctions

int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memset(void *b, int c, size_t len);

// Digits/Characters

int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

// Print

void		ft_putendl(char *s);
void		ft_putstr(char *s, int std);
void		ft_putchar(char c);
void		ft_putnbr(int n);

// List

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);

// GNL

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char		*get_next_line(int fd, int node);
void		*ft_memcpy_gnl(void *dst, const void *src, size_t n);
char		*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr_gnl(char *s, int c);
size_t		ft_strlen_gnl(const char *s);
char		*ft_free_gnl(char **str);
char		*ft_cleanline_gnl(char *str);
char		*ft_get_line_gnl(char *str);
char		*ft_reading_gnl(int fd, char *str);

// GNL UTILS

void		*ft_memcpy_gnl(void *dst, const void *src, size_t n);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr_gnl(char *s, int c);

// PIPEX

# define ERR_FLASH "Error\n"
# define ERR_ARG "Error Arg or Pipe\n"
# define ERR_PIPE "Error Pipe\n"
# define ERR_FORK "Error Fork\n"
# define ERRO_INFILE "No such file or directory\n"
# define ERRO_DUP "Error DUP\n"
# define ERRO_OUFILE "Error outfile\n"
# define ERRO_DOC "Error here doc\n"
# define ERRO_FEW "Few args\n"

typedef struct s_command t_command;

typedef struct s_fd_pipex
{
	int			processes;
	int			heredoc;
	int			n_heredocs;
	char		**limiters;
	int			i;
	int			j;
	int			count;
	int			cmd_index;
	int			cmd_start;
	int			cmd_end;
	int			append;
	int			count_fd;
	int			count_heredoc;
	char		*heredoc_path;
	int			last_type;
	int			out_index;
	char		*limiter;
	int			n_cmds;
	char		*out_file;
	pid_t		*pid;
	t_command	*commands;
	int			infile;
	int			outfile;
	int			fd;
}	t_pipex;

void		ft_cmd(t_pipex *data, char *argv, char **envir);
char		*create_path(char *possible_path, char *command);
void		free_struct(t_pipex	*data, char *message, int i, int std);
void		ft_outfile(t_pipex *data, t_token *token);
char		**cmd_managment(t_pipex *data, char *cmd);
t_command	*parse_commands(t_token *token);
char		*find_execpath(char **envir);
int			here_doc(char *limiter, const char *filename);
void		execute_command_bonus(t_pipex *data, char **args,
				char **paths, char **envir);
void		exit_with_error(char *message, int exit_code, int std);
void		ft_freedoom(char **str);
char		**split_command(char *cmd);
void		free_and_exit(char **args, char **paths, int exit_code);
void		pipex(t_token *token, char **envir);
void		free_stuct(t_pipex *data);
void		count_red_in(t_token *token, t_pipex *data);
char		*get_filename(int index);
void		delete_heredoc_files(int n);
int			get_heredoc_index(t_token *token, t_token *target);
void		init_strucs(t_pipex **data, t_command **cmds);
void		free_command_list(t_command *cmd);

void		process_and_exec(t_pipex *data, t_command *cmd,
				int i, char **envir);
void		child_process(t_pipex *data, t_command *cmd,
				int fd[2], char **envir);
void		redir_outfile(t_command *cmd);
void		redir_infile(t_command *cmd);
void		redir_heredoc(t_command *cmd);
void		parent_process(int fd[2]);
void		handle_heredoc_in_command(t_command *cmd, char *limiter, int index);
void		add_arg_to_command(t_command *cmd, char *arg);
void		add_command_to_list(t_command **head, t_command *new_cmd);
void	apply_redirections(t_command *cmd);
t_command	*init_new_command(void);
int	count_commands_list(t_command *cmd);



#endif