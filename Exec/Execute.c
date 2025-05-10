
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
	if (cmd->is_heredoc || cmd->infile)
		apply_redirections(cmd);
	if (!cmd->is_heredoc && !cmd->infile && data->prev_fd != -1)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
			exit_with_error("dup2 prev_fd failed\n", 1, 2);
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit_with_error("dup2 pipe write failed\n", 1, 2);
	close(fd[1]);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	ft_cmd(data, cmd->argv, envir);
}

void	execute_pipeline(t_pipex *data, t_command *cmds, char **envir)
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
	execute_last_command(data, curr, envir, i);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	i = 0;
	while (i++ < data->n_cmds)
		wait(NULL);
}

void	execute_last_command(t_pipex *data, t_command *curr,
	char **envir, int i)
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
		ft_cmd(data, curr->argv, envir);
	}
}

void	pipex(t_token *token, char **envir)
{
	t_pipex		*data;
	t_command	*cmds;

	data = NULL;
	cmds = NULL;
	init_strucs(&data, &cmds);
	cmds = parse_commands(token, data);
	data->n_cmds = count_commands_list(cmds);
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		exit_with_error("Error malloc pid failed\n", 1, 2);
	execute_pipeline(data, cmds, envir);
	delete_heredoc_files(data->count_heredoc);
	free_command_list(cmds);
	free_stuct(data);
}
