/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:21:01 by astefane          #+#    #+#             */
/*   Updated: 2025/05/06 13:02:20 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* static void	open_redirection(t_token *token, t_pipex *data)
{
	t_token	*tmp;
	t_token	*last_dir;

	tmp = token;
	last_dir = NULL;
	while (tmp)
	{
		if (tmp->type == T_RED_IN && tmp->next && tmp->next->value)
			last_dir = tmp;
		tmp = tmp->next;
	}
	if (!last_dir || !last_dir->next || !last_dir->next->value)
		free_struct(data, ERRO_INFILE, 1, 2);
	data->infile = open(last_dir->next->value, O_RDONLY);
	if (data->infile == -1)
		free_struct(data, ERRO_INFILE, 1, 2);
} */

/* t_token	*get_last_input(t_token *token)
{
	t_token	*last;

	last = NULL;
	while (token)
	{
		if (token->type == T_HEREDOC || token->type == T_RED_IN)
			last = token;
		token = token->next;
	}
	return (last);
}

void	ft_infile(t_token *token, t_pipex *data)
{
	t_token	*last_input;
	char	*filename;
	int		index;

	handle_all_heredocs(token, data);
	last_input = get_last_input(token);
	if (!last_input)
		return ;

	if (last_input->type == T_HEREDOC)
	{
		index = get_heredoc_index(token, last_input);
		filename = get_filename(index);
		if (!filename)
			exit_with_error("malloc failed\n", 1, 2);
		data->infile = open(filename, O_RDONLY);
		free(filename);
	}
	else if (last_input->type == T_RED_IN && last_input->next)
		data->infile = open(last_input->next->value, O_RDONLY);
	if (data->infile == -1)
		exit_with_error("aqui", 1, 2);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		exit_with_error(ERRO_DUP, 1, 2);
	close(data->infile);
} */

int	get_heredoc_index(t_token *token, t_token *target)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == T_HEREDOC)
		{
			if (token == target)
				return (i);
			i++;
		}
		token = token->next;
	}
	return (0);
}
