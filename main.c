/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:37:01 by astefane          #+#    #+#             */
/*   Updated: 2025/04/30 18:06:54 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mini.h"


static void	process_input(char *input, char **env)
{
	t_token	*list;
	t_token	*current;

	list = NULL;
	add_history(input);
	if (!fill_tokens(&list, input))
	{
		free_tokens(list);
		exit_with_error("Tokenization failed\n", 1, 1);
	}
	current = list;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
	check_type(list, env);
	free_tokens(list);
}


int	main(int argc, char **argv, char **envir)
{
	char	*input;
	int		saved_input;

	(void)argv;

	if (argc != 1)
		exit_with_error("Alot of arguments\n", 1, 1);
	
	while (1)
	{
		saved_input = dup(STDIN_FILENO);
		input = readline("Minishell> ");
		if (!input)
		{
			ft_putstr("\nLeaving...\n", 1);
			break ;
		}
		process_input(input, env);

		free(input);
		dup2(saved_input, STDIN_FILENO);
		close(saved_input);
	}
	close(saved_input);
	return (0);
}
