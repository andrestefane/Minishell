/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:23:57 by astefane          #+#    #+#             */
/*   Updated: 2025/04/29 19:24:09 by astefane         ###   ########.fr       */
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
