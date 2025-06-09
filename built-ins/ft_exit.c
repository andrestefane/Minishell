/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:25:43 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 13:12:07 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_minishell *minishell)
{
	int	code;

	ft_putstr("exit\n", 2);
	if (!minishell->command_list->argv[1])
	{
		free_minishell(minishell);
		exit(g_status);
	}
	if (minishell->command_list->argv[2])
	{
		ft_putstr(" too many arguments\n", 2);
		exit (1);
	}
	if (!is_numeric(minishell->command_list->argv[1]))
	{
		ft_putstr("exit: ", 2);
		ft_putstr(minishell->command_list->argv[1], 2);
		ft_putstr(": numeric argument required\n", 2);
		free_minishell(minishell);
		exit(2);
	}
	code = ft_atoi(minishell->command_list->argv[1]);
	free_minishell(minishell);
	exit(code % 256);
}
