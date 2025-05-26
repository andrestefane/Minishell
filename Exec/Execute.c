#include "../Mini.h"

void	process_and_exec(t_pipex *data, t_command *cmd,
		int i, t_env *envir_list)
{
	int	fd[2];

	if (pipe(fd) == -1)
		free_struct(data, ERR_PIPE, 1, 2);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		free_struct(data, ERR_FORK, 1, 2);
	if (data->pid[i] == 0)
		child_process(data, cmd, fd, envir_list);
	else
	{
		if (data->prev_fd != -1)
			close(data->prev_fd);
		data->prev_fd = fd[0];
		close(fd[1]);
	}
}

void	child_process(t_pipex *data, t_command *cmd,
		int fd[2], t_env *envir_list)
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
	ft_cmd(data, cmd->argv, envir_list);
}

void	execute_pipeline(t_minishell *mini)
{
	t_command	*curr;
	t_pipex		*data;
	t_env		*env_list;
	int			i;

	curr = mini->command_list;
	i = 0;
	data = mini->pipex_data;
	env_list = mini->env_list;
	data->prev_fd = -1;
	while (curr && i < data->n_cmds - 1)
	{
		process_and_exec(data, curr, i, env_list);
		curr = curr->next;
		i++;
	}
	execute_last_command(data, curr, i, env_list);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	wait_status(data);
}

void	execute_last_command(t_pipex *data, t_command *curr,
			int i, t_env *env_list)
{
	if (data->builtins == 1)
	{
		apply_redirections(curr);
		execute_buitin(curr, env_list);
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
			ft_cmd(data, curr->argv, env_list);
		}
	}
}


void	ft_execute(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->pipex_data = init_pipex();
	if (!mini->pipex_data)
		exit_with_error("Error init_pipex\n", 1, 2);
	mini->pipex_data->builtins = is_builtin(mini);
	mini->command_list = parse_commands(mini);
	if (!mini->command_list)
		exit_with_error("Error parsing commands\n", 1, 2);
	mini->pipex_data->n_cmds = count_commands_list(mini);
	mini->pipex_data->pid = malloc(sizeof(pid_t) * mini->pipex_data->n_cmds);
	if (!mini->pipex_data->pid)
		exit_with_error("Error malloc pid failed\n", 1, 2);
	while (i < mini->pipex_data->n_cmds)
	{
		mini->pipex_data->pid[i] = -1;
		i++;
	}
	execute_pipeline(mini);
	delete_heredoc_files(mini->pipex_data->count_heredoc);
}
