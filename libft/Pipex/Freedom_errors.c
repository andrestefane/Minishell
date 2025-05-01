/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Freedom_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:31:08 by astefane          #+#    #+#             */
/*   Updated: 2025/04/30 20:19:17 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_struct(t_pipex *data, char *message, int exit_code, int std)
{
	if (data)
	{
		if (data->pid)
		{
			free(data->pid);
			data->pid = NULL;
		}
		if (data->cmds)
		{
			ft_freedoom(data->cmds);
			data->cmds = NULL;
		}
		free(data);
	}
	ft_putstr(message, std);
	exit(exit_code);
}

void	exit_with_error(char *message, int exit_code, int std)
{
	ft_putstr(message, std);
	exit(exit_code);
}

void	ft_freedoom(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	free_and_exit(char **args, char **paths, int exit_code)
{
	ft_freedoom(args);
	ft_freedoom(paths);
	exit(exit_code);
}

void	free_stuct(t_pipex *data)
{
	int	i;

	if (data->cmds)
	{
		i = -1;
		while (data->cmds[++i])
			free(data->cmds[i]);
		free(data->cmds);
	}
	if (data->pid)
		free(data->pid);
	free(data);
}
