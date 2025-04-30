/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:37:01 by astefane          #+#    #+#             */
/*   Updated: 2025/04/30 18:13:44 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mini.h"


static void	process_input(char *input, char **envir)
{
	t_token	*list;
	int		i;

	list = &(t_token){0};
	if (*input)
	{
		add_history(input);
		list = init_token_list(input);
		if (!list)
			exit_with_error("Malloc failed\n", 1, 1);
		count_args(list);
		if (!split_tokens(list))
			exit_with_error("Split tokens failed\n", 1, 1);
		i = 0;
		while (list->tokens[i].value)
		{
			printf("Token: %s, Type: %d\n", list->tokens[i].value,
				list->tokens[i].type);
			i++;
		}
		free(list->input);
	}
	check_type(list, envir);
	free(list->tokens);
	free(list);
}


int	main(int argc, char **argv, char **envir)
{
	char	*input;
	int		saved_input;
	t_token	*list;

	list = &(t_token){0};
	char *path = find_execpath(envir);
	(void)argv;
    printf("Exec path: %s\n", path);
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
//Habra que hacer algo con esto
		process_input(input, envir, list);
		free(input);
		dup2(saved_input, STDIN_FILENO);
		close(saved_input);
	}
	close(saved_input);
	return (0);
}
