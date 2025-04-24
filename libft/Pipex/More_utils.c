/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:03:30 by astefane          #+#    #+#             */
/*   Updated: 2025/04/23 22:42:19 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_pipex	*pipex_parsing(t_token *token, t_pipex *data)
{
	int	i;

	i = 0;
// principio de linea
	if (token->tokens[i].type == T_RED_IN || token->tokens[i].type == T_HEREDOC)
	{
		data->heredoc = (token->tokens[i].type == T_HEREDOC);
		data->limiter = token->tokens[i + 1].value;
		i += 2;
	}
	data->cmd_start = -1;
	while (i < token->num_tokens)
	{
		if (token->tokens[i].type == T_PIPE && i + 1 < token->num_tokens)
		{
			data->cmd_start = i + 1;
			break ;
		}
		i++;
	}
	if (data->cmd_start == -1)
		free_struct(data, ": command not found\n", 127, 2);
// Final de linea
	data->out_index = -1;
	i = token->num_tokens - 2;
	while (i > data->cmd_start)
	{
		if (token->tokens[i].type == T_RED_OUT
			|| token->tokens[i].type == T_HEREDOC)
		{
			data->out_index = i;
			data->out_file = token->tokens[i + 1].value;
			break ;
		}
		i--;
	}
// extraer comandos entre principio y fin
	data->cmd_end = data->out_index - 1;
	data->count = 0;
	i = data->cmd_start;
	while (i <= data->cmd_end)
	{
		if (token->tokens[i].type != T_PIPE)
			data->count++;
		i++;
	}
	data->cmds = malloc(sizeof(char *) * (data->count + 1));
	if (!data->cmds)
		free_struct(data, "Malloc cmds\n", 1, 2);
	data->j = 0;
	i = data->cmd_start;
	while (i <= data->cmd_end)
	{
		if (token->tokens[i].type != T_PIPE)
			data->cmds[data->j++] = token->tokens[i].value;
		i++;
	}
	data->cmds[data->j] = NULL;
	data->n_cmds = data->j;
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		free_struct(data, "Malloc pids\n", 1, 2);
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
