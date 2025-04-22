/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:03:30 by astefane          #+#    #+#             */
/*   Updated: 2025/04/22 16:31:10 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_pipex	*pipex_parsing(int argc, char **argv, t_pipex *data)
{
	// Detectar tipo de entrada
	if (!ft_strcmp(argv[1], "_HEREDOC_"))
	{
		data->heredoc = 1;
		data->limiter = argv[2];
	}
	else if (!ft_strcmp(argv[1], "_INFILE_"))
	{
		data->heredoc = 0;
		data->limiter = argv[2];
	}
	else
		free_struct(data, "pipex: se esperaba '<' o '<<'\n", 1, 2);

	// Buscar comandos
	data->cmd_start = -1;
	data->i = 3;
	while (data->i < argc)
	{
		if (!ft_strcmp(argv[data->i], "_PIPE_") && argv[data->i + 1])
		{
			data->cmd_start = data->i + 1;
			break ;
		}
		data->i++;
	}
	if (data->cmd_start == -1)
		free_struct(data, ": command not found\n", 127, 2);

	// Detectar última redirección de salida: > o >>
	data->out_index = -1;
	data->i = argc - 2;
	while (data->i > data->cmd_start)
	{
		if (!ft_strcmp(argv[data->i], "_APPEND_") || !ft_strcmp(argv[data->i], "_OUTFILE_"))
		{
			data->out_index = data->i;
			data->out_file = argv[data->i + 1];
			break ;
		}
		data->i--;
	}
	if (data->out_index == -1 || !data->out_file)
		free_struct(data, ": missing output redirection\n", 1, 2);

	// Extraer comandos
	data->cmd_end = data->out_index - 1;
	data->i = data->cmd_start;
	while (data->i <= data->cmd_end)
	{
		if (ft_strcmp(argv[data->i], "_PIPE_") != 0)
			data->count++;
		data->i++;
	}
	data->cmds = malloc(sizeof(char *) * (data->count + 1));
	if (!data->cmds)
		free_struct(data, "Malloc cmds\n", 1, 2);

	data->i = data->cmd_start;
	while (data->i <= data->cmd_end)
	{
		if (ft_strcmp(argv[data->i], "_PIPE_") != 0)
			data->cmds[data->j++] = argv[data->i];
		data->i++;
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
