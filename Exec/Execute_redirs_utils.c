#include "../Mini.h"

int	has_redir(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (is_redir(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
