#include "../libft.h"

void	apply_redirections(t_command *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->is_heredoc == 1)
	{
		fd_in = open(cmd->heredoc_file, O_RDONLY);
		if (fd_in == -1)
			exit_with_error("Error opening heredoc\n", 1, 2);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit_with_error("Error dup2 heredoc\n", 1, 2);
		close(fd_in);
	}
	else if (cmd->infile != NULL)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in == -1)
			exit_with_error("Error opening infile\n", 1, 2);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit_with_error("Error dup2 infile\n", 1, 2);
		close(fd_in);
	}
	if (cmd->outfile != NULL)
	{
		if (cmd->append == 1)
			fd_out = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else
			fd_out = open(cmd->outfile, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		if (fd_out == -1)
			exit_with_error("Error opening outfile\n", 1, 2);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			exit_with_error("Error dup2 outfile\n", 1, 2);
		close(fd_out);
	}
}
