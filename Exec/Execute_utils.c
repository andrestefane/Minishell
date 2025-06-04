#include "../Mini.h"

// Puede ser que haya que liberar el env si falla
void	ft_cmd(t_minishell *mini)
{
	char	**possible_paths;
	char	*path_line;
	char	**envir;

	envir = env_to_array(mini->env_list);
	if (is_builtin_str(mini->command_list->argv[0]))
	{
		execute_buitin_args(mini->command_list->argv, &envir, mini->env_list);
		free_env_list(mini->env_list);
		free_pipex_data(mini->pipex_data);
		ft_freedoom(envir);
		exit(0);
	}
	if (!envir || !*envir)
		exit_with_error("Missing environment\n", 1, 2);
	path_line = find_execpath(envir);
	if (!path_line)
		exit_with_error("Error with path\n", 1, 2);
	possible_paths = ft_split(path_line, ':');
	if (!possible_paths)
		exit_with_error("Error possible path\n", 1, 2);
	free_env_list(mini->env_list);
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
			free_pipex_data(mini->pipex_data);
			ft_freedoom(paths);
			free(path);
			check_errno(errno, mini->command_list->argv);
		}
		free(path);
		i++;
	}
	(check_errno(errno, mini->command_list->argv),
		free_pipex_data(mini->pipex_data), ft_freedoom(envir),
		ft_freedoom(paths), exit(127));
}

void	check_errno(int err, char **args)
{
	if (err == EISDIR)
	{
		ft_putstr(": Is a directory\n", 2);
		(ft_freedoom(args), exit(126));
	}
	else if (err == EACCES)
	{
		if (args[0] && !ft_strchr(args[0], '/'))
			ft_putstr(": command not found\n", 2);
		else
			ft_putstr(": Permission denied\n", 2);
		(ft_freedoom(args), exit(126));
	}
	else if (err == ENOENT)
	{
		ft_putstr(": command not found\n", 2);
		(ft_freedoom(args), exit(127));
	}
	else
	{
		(ft_putstr(": ", 2), ft_putstr(strerror(err), 2),
			ft_putstr("\n", 2), ft_freedoom(args), exit(1));
	}
}
