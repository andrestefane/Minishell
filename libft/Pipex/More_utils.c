/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:03:30 by astefane          #+#    #+#             */
/*   Updated: 2025/05/01 18:39:30 by alejaro2         ###   ########.fr       */
/*   Updated: 2025/05/01 18:31:06 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_pipex	*pipex_parsing(t_token *token, t_pipex *data)
{
	first_line_pipex(token, data);
	last_line_pipex(token, data);
	count_commands(token, data);
	extract_commands(token, data);
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

void	first_line_pipex(t_token *token, t_pipex *data)
{
	t_token	*tmp;


	tmp = token;
	if (!tmp)
		free_struct(data, "Empty token list\n", 1, 2);
	data->cmd_start = -1;
	if (tmp->type == T_RED_IN || tmp->type == T_HEREDOC)
		handle_input_redirection(&tmp, data);
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			data->cmd_start = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (data->cmd_start == -1)
		free_struct(data, ": command not found\n", 127, 2);
}

void	last_line_pipex(t_token *token, t_pipex *data)
{
	t_token	*tmp;

	tmp = token;
	data->out_file = NULL;
	data->out_index = -1;

	while (tmp && tmp->next)
	{
		if (tmp->type == T_RED_OUT || tmp->type == T_RED_APPEND)
		{
			data->out_file = tmp->next->value;
			data->out_index = 1;
		}
		tmp = tmp->next;
	}
}

void	count_commands(t_token *token, t_pipex *data)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;

	while (tmp)
	{
		if (tmp->type == T_WORD)
			count++;
		if (tmp->type == T_RED_OUT || tmp->type == T_RED_APPEND)
			break ;
		tmp = tmp->next;
	}
	data->count = count;
	data->cmds = malloc(sizeof(char *) * (count + 1));
	if (!data->cmds)
		free_struct(data, "Malloc cmds\n", 1, 2);
}

void	extract_commands(t_token *token, t_pipex *data)
{
	t_token	*tmp;
	int		j;

	tmp = token;
	j = 0;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			data->cmds[j] = ft_strdup(tmp->value);
			if (!data->cmds[j])
				free_struct(data, "Malloc ft_strdup\n", 1, 2);
			j++;
		}
		if (tmp->type == T_RED_OUT || tmp->type == T_RED_APPEND)
			break ;
		tmp = tmp->next;
	}
	data->cmds[j] = NULL;
	data->n_cmds = j;
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		free_struct(data, "Malloc pids\n", 1, 2);
}
