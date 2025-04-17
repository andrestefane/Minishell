/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:03:30 by astefane          #+#    #+#             */
/*   Updated: 2025/04/17 18:32:08 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_fd_pipex	*bonus_struct(int argc, char **argv)
{
	t_fd_pipex	*data;

	if (argc < 5)
		exit_with_error(ERRO_FEW, 0);
	data = malloc(sizeof(t_fd_pipex));
	if (!data)
		return (NULL);
	if (!ft_strcmp(argv[1], "here_doc"))
		data->heredoc = 1;
	else
		data->heredoc = 0;
	data->processes = (argc - 3) - data->heredoc;
	data->pid = malloc(data->processes * sizeof(pid_t));
	if (!data->pid)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

char	**split_command(char *cmd)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_freedoom(cmd_split);
		return (NULL);
	}
	return (cmd_split);
}
