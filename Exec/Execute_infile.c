
#include "../Mini.h"

void	apply_infile(t_command *cmd)
{
	int	fd_in;

	fd_in = open(cmd->infile, O_RDONLY);
	if (fd_in == -1)
		exit_with_error("Error opening infile\n", 1, 2);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_with_error("Error dup2 infile\n", 1, 2);
	close(fd_in);
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
