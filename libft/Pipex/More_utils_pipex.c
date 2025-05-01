/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:23:57 by astefane          #+#    #+#             */
/*   Updated: 2025/05/01 18:39:21 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	extract_commands(t_token *token, t_pipex *data)
{
	int	i;

	data->j = 0;
	i = data->cmd_start;
	while (i <= data->cmd_end)
	{
		if (token->tokens[i].type != T_PIPE)
		{
			data->cmds[data->j] = ft_strdup(token->tokens[i].value);
			if (!data->cmds[data->j++])
				free_struct(data, "Malloc ft_strdup\n", 1, 2);
		}
		i++;
	}
	data->cmds[data->j] = NULL;
	data->n_cmds = data->j;
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		free_struct(data, "Malloc pids\n", 1, 2);
}
