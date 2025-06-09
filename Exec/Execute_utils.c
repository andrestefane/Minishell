/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:21:25 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 15:25:35 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	ft_cmd(t_minishell *mini)
{
	char	**possible_paths;
	char	*path_line;
	char	**envir;

	envir = env_to_array(mini->env_list);
	if (is_builtin_str(mini->command_list->argv[0]))
	{
		execute_buitin_args(mini->command_list->argv, &envir, mini);
		ft_freedoom(envir);
		free_minishell(mini);
		exit(0);
	}
	if (!envir || !*envir)
		(exit_with_error("Missing environment\n", 1, 2), free_minishell(mini),
			ft_freedoom(envir));
	path_line = find_execpath(envir);
	if (!path_line)
		(exit_with_error("Error with path\n", 1, 2), free_minishell(mini),
			ft_freedoom(envir));
	possible_paths = ft_split(path_line, ':');
	if (!possible_paths)
		(exit_with_error("Error with possible path\n", 1, 2),
			free_minishell(mini), ft_freedoom(envir));
	execute_command(mini, possible_paths, envir);
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
	free(temp);
	return (path);
}

void	execute_command(t_minishell *mini, char **paths, char **envir)
{
	char	*path;
	int		i;

	if (!envir || !*envir)
		free_struct(mini->pipex_data, "Missing environment\n", 1, 2);
	i = 0;
	while (paths[i] != NULL)
	{
		path = create_path(paths[i], mini->command_list->argv[0]);
		if (!path)
			free_and_exit(mini->command_list->argv, paths, 0);
		if (access(path, F_OK) != -1 && access(path, X_OK) == 0)
		{
			execve(path, mini->command_list->argv, envir);
			/* free(path); */
			check_errno(errno, mini);
		}
		free(path);
		i++;
	}
	mini->paths_execve = paths;
	mini->envir_execve = envir;
	(check_errno(errno, mini), exit(127));
}

void	check_errno(int err, t_minishell *mini)
{
	if (err == EISDIR)
	{
		ft_putstr(": Is a directory\n", 2);
		(free_minishell(mini), exit(126));
	}
	else if (err == EACCES)
	{
		if (mini->command_list->argv[0]
			&& !ft_strchr(mini->command_list->argv[0], '/'))
			ft_putstr(": command not found\n", 2);
		else
			ft_putstr(": Permission denied\n", 2);
		(free_minishell(mini), exit(126));
	}
	else if (err == ENOENT)
	{
		ft_putstr(": command not found\n", 2);
		(free_minishell(mini), exit(127));
	}
	else
	{
		(ft_putstr(": ", 2), ft_putstr(strerror(err), 2),
			ft_putstr("\n", 2), free_minishell(mini), exit(1));
	}
}
