/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:35:27 by astefane          #+#    #+#             */
/*   Updated: 2025/04/23 20:33:45 by astefane         ###   ########.fr       */
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
	T_HEREDOC,
	T_INFILE,
	T_OUTFILE

}	t_token_type;

typedef struct s_single_token //almacena informacion de un token individual
{
	char  *value; // su valor
	t_token_type type; // su tipo
}t_single_token;

typedef struct s_token
{
	char *input;
	int num_tokens;
	t_single_token *tokens; // puntero a un bloque de memoria que almacena múltiples t_single_token consecutivos.
}t_token;



// Tokens
t_token	*init_token_list(char *input);
void	count_args(t_token *list);
int	split_tokens(t_token *list);
char *extract_token(char *input, int *index, t_token_type *type);


// Exec
void	check_type(t_token *token, char **envir);


#endif
