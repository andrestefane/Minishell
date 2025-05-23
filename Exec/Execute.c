#include "../Mini.h"

void	process_and_exec(t_pipex *data, t_command *cmd, int i, char **envir)
{
	int	fd[2];

	if (pipe(fd) == -1)
		free_struct(data, ERR_PIPE, 1, 2);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		free_struct(data, ERR_FORK, 1, 2);
	if (data->pid[i] == 0)
		child_process(data, cmd, fd, envir);
	else
	{
		if (data->prev_fd != -1)
			close(data->prev_fd);
		data->prev_fd = fd[0];
		close(fd[1]);
	}
}

void	child_process(t_pipex *data, t_command *cmd, int fd[2], char **envir)
{
	apply_redirections(cmd);
	if (!has_redir_type(cmd, T_RED_IN)
		&& !has_redir_type(cmd, T_HEREDOC) && data->prev_fd != -1)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
			exit_with_error("dup2 prev_fd failed\n", 1, 2);
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (!has_redir_type(cmd, T_RED_OUT) && !has_redir_type(cmd, T_RED_APPEND))
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_with_error("dup2 pipe write failed\n", 1, 2);
	}
	close(fd[0]);
	close(fd[1]);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	ft_cmd(data, cmd->argv, envir);
}

void	execute_pipeline(t_pipex *data, t_command *cmds,
	char **envir, t_env **env_list)
{
	t_command	*curr;
	int			i;

	curr = cmds;
	i = 0;
	data->prev_fd = -1;
	while (curr && i < data->n_cmds - 1)
	{
		process_and_exec(data, curr, i, envir);
		curr = curr->next;
		i++;
	}
	execute_last_command(data, curr, envir, i, env_list);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	wait_status(data);
}

void	execute_last_command(t_pipex *data, t_command *curr,

		char **envir, int i, t_env **env_list)

{
	if (data->builtins == 1)
	{
		apply_redirections(curr);
		execute_buitin(curr, &envir, env_list);

		if (data->prev_fd != -1)
			close(data->prev_fd);
	}
	else
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			free_struct(data, ERR_FORK, 1, 2);
		if (data->pid[i] == 0)
		{
			if (data->prev_fd != -1)
			{
				if (dup2(data->prev_fd, STDIN_FILENO) == -1)
					exit_with_error("dup2 final prev_fd failed\n", 1, 2);
				close(data->prev_fd);
			}
			apply_redirections(curr);
			if (!curr->argv || !curr->argv[0])
				exit(0);
			ft_cmd(data, curr->argv, envir);
		}
	}
}

void	ft_execute(t_token *token, char **envir, t_env **env_list)
{
	t_pipex		*data;
	t_command	*cmds;

	data = NULL;
	cmds = NULL;
	/* expand_token(token); */
	init_strucs(&data, &cmds);
	data->builtins = is_builtin(token);
	cmds = parse_commands(token, data);
	data->n_cmds = count_commands_list(cmds);
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		exit_with_error("Error malloc pid failed\n", 1, 2);
	for (int i = 0; i < data->n_cmds; i++)
	data->pid[i] = -1;
	execute_pipeline(data, cmds, envir, env_list);

	delete_heredoc_files(data->count_heredoc);
	free_command_list(cmds);
	free_stuct(data);
}
