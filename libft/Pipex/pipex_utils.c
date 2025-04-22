/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:06:04 by astefane          #+#    #+#             */
/*   Updated: 2025/04/22 16:27:24 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_cmd(t_pipex *data, char *argv, char **envir)
{
	char	**args;
	char	**possible_paths;
	char	*path_line;

	if (!envir || !*envir)
		return ;
	args = cmd_managment(data, argv);
	if (!args || !*args)
		free_struct(data, "Error with args\n", 1, 2);
	path_line = find_execpath(envir);
	if (!path_line)
	{
		ft_freedoom(args);
		exit_with_error("Error with path\n", 1, 2);
	}
	possible_paths = ft_split(path_line, ':');
	if (!possible_paths)
	{
		ft_freedoom(args);
		exit_with_error("Error possible path\n", 1, 2);
	}
	execute_command_bonus(data, args, possible_paths, envir);
}

char	**cmd_managment(t_pipex *data, char *cmd)
{
	char	**cmd_split;
	char	*cmd_only;
	char	*arg_only;

	if (!cmd || !*cmd)
		free_struct(data, "Error cmd_managment\n", 1, 2);
	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_freedoom(cmd_split);
		return (NULL);
	}
	cmd_only = ft_strdup(cmd_split[0]);
	ft_freedoom(cmd_split);
	arg_only = ft_strchr(cmd, 39);
	if (!arg_only)
	{
		free(cmd_only);
		return (split_command(cmd));
	}
	cmd_split = malloc(sizeof(char *) * 3);
	if (!cmd_split)
		free_struct(data, "Error cmd_split\n", 1, 2);
	cmd_split = (char *[]){cmd_only, ft_strtrim(arg_only, "'"), NULL};
	return (cmd_split);
}

char	*find_execpath(char **envir)
{
	int	i;

	i = 0;
	if (!envir)
		return (NULL);
	while (envir[i])
	{
		if (ft_strncmp(envir[i], "PATH=", 5) == 0)
			return (envir[i] + 5);
		i++;
	}
	return (NULL);
}

void	execute_command_bonus(t_pipex *data, char **args,
char **paths, char **envir)
{
	char	*path;
	int		i;

	if (!envir || !*envir)
		return ;
	i = 0;
	while (paths[i] != NULL)
	{
		path = create_path(paths[i], args[0]);
		if (!path)
			free_and_exit(args, paths, 0);
		if (access(path, X_OK) != -1)
			execve(path, args, envir);
		free(path);
		i++;
	}
	write(2, "Error execution\n", 17);
	ft_putstr(args[0], 2);
	free(data->pid);
	free(data);
	free_and_exit(args, paths, 127);
}

char	*create_path(char *possible_path, char *command)
{
	char	*path;
	char	*temp;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	temp = ft_strjoin(possible_path, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, command);
	return (path);
}
