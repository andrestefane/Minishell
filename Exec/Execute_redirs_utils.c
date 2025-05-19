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

int	token_has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}
