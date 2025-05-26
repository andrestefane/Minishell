#include "../Mini.h"

// Puede ser que haya que liberar el env si falla
void	ft_cmd(t_pipex *data, char **argv, t_env *env_list)
{
	char	**possible_paths;
	char	*path_line;
	char	**envir;

	envir = env_to_array(env_list);
	if (is_builtin_str(argv[0]))
	{
		execute_buitin_args(argv, &envir);
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
	execute_command(data, argv, possible_paths, envir);
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
		return (ft_freedoom(cmd_split), NULL);
	cmd_only = ft_strdup(cmd_split[0]);
	ft_freedoom(cmd_split);
	arg_only = ft_strchr(cmd, 39);
	if (!arg_only)
		return (free(cmd_only), split_command(cmd));
	cmd_split = malloc(sizeof(char *) * 3);
	if (!cmd_split)
		free_struct(data, "Error cmd_split\n", 1, 2);
	cmd_split[0] = cmd_only;
	cmd_split[1] = ft_strtrim(arg_only, "'");
	cmd_split[2] = NULL;
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

void	execute_command(t_pipex *data, char **args,
char **paths, char **envir)
{
	char	*path;
	int		i;

	if (!envir || !*envir)
		free_struct(data, "Missing environment\n", 1, 2);
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
	ft_putstr(args[0], 2);
	ft_putstr(": Command not found\n", 2);
	free(data->pid);
	free(data);
	free_and_exit(args, paths, 127);
}
