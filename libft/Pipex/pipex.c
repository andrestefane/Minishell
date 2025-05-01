/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:37:18 by astefane          #+#    #+#             */
/*   Updated: 2025/04/30 20:18:48 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	process_and_exec(t_pipex *data, int i, char **envir)
{
	int		fd[2];

	if (pipe(fd) == -1)
		free_struct(data, ERR_PIPE, 1, 2);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		free_struct(data, ERR_FORK, 1, 2);
	if (data->pid[i] == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_cmd(data, data->cmds[data->i], envir);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	pipex(t_token *token, char **envir)
{
	t_pipex	*data;

	data = malloc(sizeof(t_pipex));
	if (!data)
		return ;
	ft_memset(data, 0, sizeof(t_pipex));
	data = pipex_parsing(token, data);
	ft_infile(token, data);
	ft_outfile(data, token);
	data->i = -1;
	while (++data->i < data->n_cmds - 1)
		process_and_exec(data, data->i, envir);
	if (data->heredoc == 1)
		unlink("here_doc.temp");
	data->pid[data->i] = fork();
	if (!data->pid[data->i])
	{
		dup2(data->outfile, STDOUT_FILENO);
		ft_cmd(data, data->cmds[data->i], envir);
	}
	data->i = 0;
	while (data->i++ < data->processes)
		wait(NULL);
	free_stuct(data);
}
