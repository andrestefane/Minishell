
#include "../Mini.h"

void	free_and_error(char *str, char *message, int exit_code, int std)
{
	free(str);
	ft_putstr(message, std);
	exit(exit_code);
}

void	free_stuct(t_pipex *data)
{
	if (data->pid)
		free(data->pid);
	free(data);
}
