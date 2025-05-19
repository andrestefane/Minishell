#include "../Mini.h"

void	wait_status(t_pipex *data)
{
	int		status;
	pid_t	pid;
	int		count;

	count = 0;
	while (count < data->n_cmds)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			exit_with_error("Waitpid failed\n", 1, 2);
		if (pid == data->pid[data->n_cmds - 1])
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_status = 128 + WTERMSIG(status);
		}
		count++;
	}
}
