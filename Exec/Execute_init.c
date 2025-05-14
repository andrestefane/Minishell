
#include "../Mini.h"

void	init_strucs(t_pipex **data, t_command **cmds)
{
	*cmds = init_new_command();
	*data = malloc(sizeof(t_pipex));
	if (!cmds || !data)
		return ;
	ft_memset(*data, 0, sizeof(t_pipex));
}

t_command	*init_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->heredoc_file = NULL;
	cmd->next = NULL;
	return (cmd);
}
