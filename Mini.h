/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:35:27 by astefane          #+#    #+#             */
/*   Updated: 2025/04/22 16:24:34 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H

# define MINI_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_RED_IN,
	T_RED_OUT,
	T_RED_APPEND,
	T_HEREDOC
}t_token_type;

typedef struct s_single_token
{
	char  *value;
	t_token_type type;
}t_single_token;

typedef struct s_token
{
	t_single_token *tokens;
	char *input;
	int num_tokens;
}t_token;



// Tokens
// t_token *tokenizer(char *input);

// Ejecucion
void	ft_exec(t_token *list);

// Utilidades
void	exit_with_error(char *message, int exit_code);

char *extract_token(char *input, int *index, t_token_type *type);

#endif
