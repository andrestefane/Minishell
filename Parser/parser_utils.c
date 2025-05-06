#include "../Mini.h"

void	free_commands(t_command *cmd)
{
	int i;

	i = 0;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}

	free(cmd->argv);
	free(cmd);
}
