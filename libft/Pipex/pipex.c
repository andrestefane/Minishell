/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:37:18 by astefane          #+#    #+#             */
/*   Updated: 2025/04/22 16:30:23 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_infile(char **argv, t_pipex *data)
{
	if (!argv[1])
		free_struct(data, ERRO_INFILE, 1, 2);
	if (data->heredoc == 0)
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile == -1)
			free_struct(data, ERRO_INFILE, 1, 2);
	}
	else
	{
		here_doc(argv);
		data->infile = open("here_doc.temp", O_RDONLY, 0744);
		if (data->infile == -1)
			free_struct(data, ERRO_DOC, 1, 2);
	}
	if (data->infile == -1)
		exit_with_error(ERRO_INFILE, 1, 2);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		exit_with_error(ERRO_DUP, 1, 2);
	close(data->infile);
}

void	ft_outfile(t_pipex *data, int argc, char **argv)
{
	if (!argv[argc - 1])
		free_struct(data, ERRO_OUFILE, 1, 2);
	if (data->heredoc == 1)
		data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY
				| O_APPEND, 0644);
	else
		data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY
				| O_TRUNC, 0644);
	if (data->outfile == -1)
		free_struct(data, ERRO_OUFILE, 1, 2);
}

int	here_doc(char **argv)
{
	int		infile;
	char	*line;

	infile = open("here_doc.temp", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (infile == -1)
	{
		unlink("here_doc");
		exit_with_error(ERRO_DOC, 1, 2);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
			&& line[ft_strlen(argv[2])] == '\n')
			break ;
		write(infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(infile);
	return (infile);
}

void	process_and_exec(t_pipex *data, int i, char **argv, char **envir)
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
		ft_cmd(data, argv[2 + i + data->heredoc], envir);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

int	pipex(int argc, char **argv, char **envir)
{
	t_pipex	*data;

	data = malloc(sizeof(t_pipex));
	if (!data)
		return (0);
	ft_memset(data, 0, sizeof(t_pipex));
	data = pipex_parsing(argc, argv, data);
	ft_infile(argv, data);
	ft_outfile(data, argc, argv);
	data->i = 0;
	while (data->i < data->processes - 1)
		process_and_exec(data, data->i++, argv, envir);
	if (data->heredoc == 1)
		unlink("here_doc.temp");
	data->pid[data->i] = fork();
	if (!data->pid[data->i])
	{
		dup2(data->outfile, STDOUT_FILENO);
		ft_cmd(data, argv[argc - 2], envir);
	}
	data->i = 0;
	while (data->i++ < data->processes)
		wait(NULL);
	free(data->pid);
	free(data);
	return (0);
}
