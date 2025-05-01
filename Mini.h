/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:35:27 by astefane          #+#    #+#             */
/*   Updated: 2025/05/01 16:54:27 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H

# define MINI_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

#define NORMAL MODE 0
#define DOUBLE_MODE 1
#define SIMPLE_MODE 2

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
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_tokenizer {
    char    *input;         // String completo
    int     position;       // Posición actual
    int     mode;           // Estado actual (NORMAL/DOUBLE/SIMPLE)
} t_tokenizer;

typedef enum e_expansion_type
{
	NO_EXPANSION,
	TILDE_EXPANSION,
	VAR_EXPANSION,
	EXIT_STATUS_EXPANSION
}	t_expansion_type;

// Tokens
void				add_token(t_token **head, char *value, t_token_type type);
t_token_type		get_operator_type(char *input, int i, int *len);
char				*extract_token_aux(char *input, int *index, t_token_type *type, t_token_type prev_type);
char *extract_word(char *input, int *index, int start);
void	free_tokens(t_token *head);
int fill_tokens(t_token **token_list, char *input); 
// Exec
void				check_type(t_token *token, char **env);
char *extract_token(char *input, int *index, t_token_type *type, t_token_type prev_type);

//Variables
void	expand_token(t_token *token, char **env);
int		is_simple_quotes(char *str);
// void	expand_tilde(t_single_token *token, char **env);
#endif

