
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
	ft_cmd(data, *cmd->argv, envir);
}

void	redir_outfile(t_command *cmd)
{
	int	fd_out;

	if (cmd->append == 1)
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_with_error("Error opening outfile\n", 1, 2);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_with_error("Error doing dup2 outfile\n", 1, 2);
	close(fd_out);
}


void	redir_infile(t_command *cmd)
{
	int	fd_in;

	fd_in = open(cmd->infile, O_RDONLY);
	if (fd_in == -1)
		exit_with_error("Error opening infile\n", 1, 2);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_with_error("Error doing dup2 infile\n", 1, 2);
	close(fd_in);
}

void	redir_heredoc(t_command *cmd)
{
	int	fd_in;

	fd_in = open(cmd->heredoc_file, O_RDONLY);
	if (fd_in == -1)
		exit_with_error("Error opening heredoc\n", 1, 2);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_with_error("Error doing dup2 heredoc\n", 1, 2);
	close(fd_in);
}

void	parent_process(int fd[2])
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit_with_error("Dup2 pipe read error\n", 1, 2);
	close(fd[0]);
}

void	init_strucs(t_pipex **data, t_command **cmds)
{
	*cmds = malloc(sizeof(t_command));
	*data = malloc(sizeof(t_pipex));
	if (!cmds || !data)
		return ;
	ft_memset(*data, 0, sizeof(t_pipex));
	ft_memset(*cmds, 0, sizeof(t_pipex));

}

void	pipex(t_token *token, char **envir)
{
	t_pipex		*data;
	t_command	*cmds;
	t_command	*curr;
	int			i;

	i = 0;
	init_strucs(&data, &cmds);
	cmds = parse_commands(token);
	curr = cmds;
	data->n_cmds = count_commands_list(cmds);
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		exit_with_error("Error malloc pid failed\n", 1, 2);
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
		ft_cmd(data, *curr->argv, envir);
	}
	i = 0;
	while (i++ < data->processes)
		wait(NULL);
	delete_heredoc_files(data->count_heredoc);
	free_command_list(cmds);
	free_stuct(data);
}
