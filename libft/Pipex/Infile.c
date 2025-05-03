/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:21:01 by astefane          #+#    #+#             */
/*   Updated: 2025/05/03 14:31:42 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	open_redirection(t_token *token, t_pipex *data)
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
}

void	ft_infile(t_token *token, t_pipex *data)
{
	if (data->heredoc_path)
		data->infile = open(data->heredoc_path, O_RDONLY);
	else if (data->count_fd > 0)
		open_redirection(token, data);
	else
		return ;
	if (data->infile == -1)
		exit_with_error(ERRO_INFILE, 1, 2);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		exit_with_error(ERRO_DUP, 1, 2);
	close(data->infile);
}
