/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:03:30 by astefane          #+#    #+#             */
/*   Updated: 2025/05/01 18:39:30 by alejaro2         ###   ########.fr       */
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
	int	i = 0;

	// Detectar redirección de entrada al inicio
	if (token->type == T_RED_IN || token->type == T_HEREDOC)
	{
		data->heredoc = (token->type == T_HEREDOC);
		data->limiter = token->next;
		i += 2;
	}

	// Buscar el primer comando real (ignorar redirecciones y pipes)
	while (i < token->num_tokens)
	{
		if (token->tokens[i].type == T_WORD)
		{
			data->cmd_start = i;
			break;
		}
		i++;
	}

	if (data->cmd_start == -1)
		free_struct(data, ": command not found\n", 127, 2);
}

void	last_line_pipex(t_token *token, t_pipex *data)
{
	int	i;

	data->out_index = -1;
	data->out_file = NULL;
	i = token->num_tokens - 2; 
// Buscar desde el final hacia cmd_start
	while (i > data->cmd_start)
	{
		if (token->tokens[i].type == T_RED_OUT
			|| token->tokens[i].type == T_RED_APPEND)
		{
			data->out_index = i;
			data->out_file = token->tokens[i + 1].value;
			break ;
		}
		i--;
	}
}

void	count_commands(t_token *token, t_pipex *data)
{
	int	i;

	if (data->out_index != -1)
		data->cmd_end = data->out_index - 1;
	else
		data->cmd_end = token->num_tokens - 1;
	data->count = 0;
	i = data->cmd_start;
	while (i <= data->cmd_end)
	{
		if (token->tokens[i++].type != T_PIPE)
			data->count++;
	}
	data->cmds = malloc(sizeof(char *) * (data->count + 1));
	if (!data->cmds)
		free_struct(data, "Malloc cmds\n", 1, 2);
}
