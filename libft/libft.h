/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:05:07 by astefane          #+#    #+#             */
/*   Updated: 2025/04/12 18:17:13 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Memory

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);

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
void		ft_putstr(char *s);
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
char		*ft_reading(int fd, char *str);
char		*ft_cleanline(char *str);
char		*ft_free(char **str);
char		*ft_get_line(char *str);

// GNL UTILS

void		*ft_memcpy_gnl(void *dst, const void *src, size_t n);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr_gnl(char *s, int c);

// PIPEX

# define ERR_FLASH "Error"
# define ERR_ARG "Error Arg or Pipe"
# define ERR_PIPE "Error Pipe"
# define ERR_FORK "Error Fork"
# define ERRO_INFILE "Error infile"
# define ERRO_DUP "Error DUP"
# define ERRO_OUFILE "Error outfile"
# define ERRO_DOC "Error here doc"
# define ERRO_FEW "Few args"

typedef struct s_fd_pipex
{
	int		processes;
	int		heredoc;
	int		infile;
	int		outfile;
	pid_t	*pid;
}	t_fd_pipex;

void		ft_cmd(t_fd_pipex *data, char *argv, char **envir);
char		*create_path(char *possible_path, char *command);
void		free_struct(t_fd_pipex	*data, char *message, int i);
void		ft_outfile(t_fd_pipex *data, int argc, char **argv);
char		**cmd_managment(t_fd_pipex *data, char *cmd);
void		ft_infile(char **argv, t_fd_pipex *data);
t_fd_pipex	*bonus_struct(int argc, char **argv);
char		*find_execpath(char **envir);
int			here_doc(char **argv);

void		execute_command(t_fd_pipex *data, char **args,
				char **paths, char **envir);
void		process_and_exec(t_fd_pipex *data, int i,
				char **argv, char **envir);
void		exit_with_error(char *message, int exit_code);
void		ft_freedoom(char **str);
char		**split_command(char *cmd);
void		free_and_exit(char **args, char **paths, int exit_code);
int			pipex(int argc, char **argv, char **envir);

#endif