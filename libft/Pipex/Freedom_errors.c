/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Freedom_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:31:08 by astefane          #+#    #+#             */
/*   Updated: 2025/04/12 17:31:41 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_struct(t_fd_pipex	*data, char *message, int i)
{
	if (data)
	{
		free(data->pid);
		free(data);
		ft_putstr(message);
		exit(i);
	}
}

void	exit_with_error(char *message, int exit_code)
{
	ft_putstr(message);
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
	free (str);
	str = NULL;
}

void	free_and_exit(char **args, char **paths, int exit_code)
{
	ft_freedoom(args);
	ft_freedoom(paths);
	exit(exit_code);
}
