/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:28:37 by astefane          #+#    #+#             */
/*   Updated: 2025/04/17 19:15:10 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	count_args(t_token *list)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (list->tokens[count])
		list->num_tokens++;
}

void	split_tokens(t_token *list)
{
	int	i;

	i = 0;
	while (list->input[i])
	{
		list->tokens[i] = *ft_split(&list->input[i], ' ');
		i++;
	}
	list->tokens[i] = NULL;
}

void	tokenizer(t_token *list)
{
	count_args(list);
	split_tokens(list);
}
