/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:21:01 by astefane          #+#    #+#             */
/*   Updated: 2025/04/30 20:19:46 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	open_redirection(t_token *token, t_pipex *data)
{
	t_token	*next;

	next = token->next;
	if (!next || !next->value)
		free_struct(data, ERRO_INFILE, 1, 2);
	data->infile = open(next->value, O_RDONLY);
	if (data->infile == -1)
		free_struct(data, ERRO_INFILE, 1, 2);
}

static void	open_heredoc(t_token *token, t_pipex *data)
{
	here_doc(token);
	data->infile = open("here_doc.temp", O_RDONLY, 0744);
	if (data->infile == -1)
		free_struct(data, ERRO_DOC, 1, 2);
}

void	ft_infile(t_token *token, t_pipex *data)
{
	if (data->heredoc == 0)
		open_redirection(token, data);
	else
		open_heredoc(token, data);
	if (data->infile == -1)
		exit_with_error(ERRO_INFILE, 1, 2);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		exit_with_error(ERRO_DUP, 1, 2);
	close(data->infile);
}
