#include "../libft.h"

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
		parent_process(fd);
}

void	child_process(t_pipex *data, t_command *cmd, int fd[2], char **envir)
{
	if (cmd->is_heredoc == 1)
		redir_heredoc(cmd);
	else if (cmd->infile != NULL)
		redir_infile(cmd);
	if (cmd->outfile != NULL)
		redir_outfile(cmd);
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit_with_error("Dup2 pipe write error\n", 1, 2);
	close(fd[1]);
	ft_cmd(data, cmd->argv, envir);
}

void	parent_process(int fd[2])
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit_with_error("Dup2 pipe read error\n", 1, 2);
	close(fd[0]);
}

void	execute_pipeline(t_pipex *data, t_command *cmds, char **envir)
{
	t_command	*curr;
	int			i;

	curr = cmds;
	i = 0;
	while (curr && i < data->n_cmds - 1)
	{
		process_and_exec(data, curr, i, envir);
		curr = curr->next;
		i++;
	}
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		free_struct(data, ERR_FORK, 1, 2);
	if (data->pid[i] == 0)
	{
		apply_redirections(curr);
		ft_cmd(data, curr->argv, envir);
	}
	i = 0;
	while (i++ < data->processes)
		wait(NULL);
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
