/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:05:43 by astefane          #+#    #+#             */
/*   Updated: 2025/04/17 19:09:38 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	ft_exec(t_token *list)
{
	while (1)
	{
		list->input = readline("Minishell> ");
		if (list->input == NULL)
		{
			ft_putstr("\nLeaving...\n");
			break ;
		}
		if (*list->input)
			add_history(list->input);
		list->tokens = ft_split(list->input, ' ');
		if (!list->tokens)
			exit_with_error("Error in count args\n", 1);
		tokenizer(list);
		/* if (list->num_tokens > 0)
			pipex(list->num_tokens, list->tokens, env); */
		for (int i = 0; i < list->num_tokens; i++) //esto sobrara
			printf("%s", list->tokens[i]);
		free(list->tokens);
		free(list->input);
	}
}
