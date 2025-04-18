/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:35:27 by astefane          #+#    #+#             */
/*   Updated: 2025/04/17 19:10:59 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct tokens
{
	char	**tokens;
	char	*input;
	int		num_tokens;

}	t_token;

// Tokens
void	tokenizer(t_token *list);
void	count_args(t_token *list);

// Ejecucion
void	ft_exec(t_token *list);

#endif