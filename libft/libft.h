/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:05:07 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 16:02:55 by astefane         ###   ########.fr       */
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
size_t		ft_strcat(char *dst, const char *src);
size_t		ft_strcpy(char *dest, const char *src);
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

#endif