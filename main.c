/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:37:01 by astefane          #+#    #+#             */
/*   Updated: 2025/04/12 18:39:39 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mini.h"

int	main(int argc, char **argv, char **env)
{
	char *input;
    char prompt[] = "Minishell> ";
	while (1)
	{
		input = readline(prompt);
		pipex(argc, argv, env);
		if (input == NULL)
		{
			ft_putstr("\nLeaving...\n");
			break ;
		}
		if (*input)
			add_history(input);
		ft_putstr(input);
		/* free(input); */
	}
	return (0);
}
