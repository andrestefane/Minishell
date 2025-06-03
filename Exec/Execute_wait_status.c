#include "../Mini.h"

void	wait_status(t_pipex *data)
{
	int		status;
	pid_t	pid;
	int		count;

	count = 0;
	while (count < data->n_cmds)
	{
		if (data->pid[count] > 0)
		{
			pid = waitpid(data->pid[count], &status, 0);
			if (pid == -1)
				perror("waitpid");
		}
		if (pid == -1)
			exit_with_error("Waitpid failed\n", 1, 2);
		/* printf("status dentro del puto bucle: %d\n", WEXITSTATUS(status)); */
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
