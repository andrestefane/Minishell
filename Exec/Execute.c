#include "../Mini.h"

void	process_and_exec(t_minishell *mini, int i)
{
	int	fd[2];

	if (pipe(fd) == -1)
		free_struct(mini->pipex_data, ERR_PIPE, 1, 2);
	mini->pipex_data->pid[i] = fork();
	if (mini->pipex_data->pid[i] == -1)
		free_struct(mini->pipex_data, ERR_FORK, 1, 2);
	if (mini->pipex_data->pid[i] == 0)
		child_process(mini, fd);
	else
	{
		if (mini->pipex_data->prev_fd != -1)
			close(mini->pipex_data->prev_fd);
		mini->pipex_data->prev_fd = fd[0];
		close(fd[1]);
	}
}

void	child_process(t_minishell *mini, int fd[2])
{
	apply_redirections(mini);
	if (!has_redir_type(mini->command_list, T_RED_IN)
		&& !has_redir_type(mini->command_list, T_HEREDOC)
		&& mini->pipex_data->prev_fd != -1)
	{
		if (dup2(mini->pipex_data->prev_fd, STDIN_FILENO) == -1)
			exit_with_error("dup2 prev_fd failed\n", 1, 2);
	}
	if (mini->pipex_data->prev_fd != -1)
		close(mini->pipex_data->prev_fd);
	if (!has_redir_type(mini->command_list, T_RED_OUT)
		&& !has_redir_type(mini->command_list, T_RED_APPEND))
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_with_error("dup2 pipe write failed\n", 1, 2);
	}
	close(fd[0]);
	close(fd[1]);
	if (!mini->command_list->argv || !mini->command_list->argv[0])
		exit(0);
	ft_cmd(mini);
}

void	execute_pipeline(t_minishell *mini)
{
	int			i;

	i = 0;
	while (mini->command_list && i < mini->pipex_data->n_cmds - 1)
	{
		process_and_exec(mini, i);
		mini->command_list = mini->command_list->next;
		i++;
	}
	execute_last_command(mini, mini->command_list, i);
	if (mini->pipex_data->prev_fd != -1)
		close(mini->pipex_data->prev_fd);
	wait_status(mini->pipex_data);
}

void	execute_last_command(t_minishell *mini, t_command *curr, int i)
{
	if (mini->pipex_data->builtins == 1)
	{
		apply_redirections(curr);
		execute_buitin(curr, mini->env_list, mini);
		if (mini->pipex_data->prev_fd != -1)
			close(mini->pipex_data->prev_fd);
	}
	else
	{
		mini->pipex_data->pid[i] = fork();
		if (mini->pipex_data->pid[i] == -1)
			free_struct(mini->pipex_data, ERR_FORK, 1, 2);
		if (mini->pipex_data->pid[i] == 0)
		{
			if (mini->pipex_data->prev_fd != -1)
			{
				if (dup2(mini->pipex_data->prev_fd, STDIN_FILENO) == -1)
					exit_with_error("dup2 final prev_fd failed\n", 1, 2);
				close(mini->pipex_data->prev_fd);
			}
			apply_redirections(curr);
			if (!curr->argv || !curr->argv[0])
				exit(0);
			ft_cmd(mini);
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
	mini->pipex_data->commands = mini->command_list;
	/* if (!mini->command_list)
		exit_with_error("Error parsing commands\n", 1, 2); */
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
