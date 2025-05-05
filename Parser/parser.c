#include "../Mini.h"

t_command	*parse_single_command(t_token *tokens)
{
	t_command	*cmd;
	int			argc;
	t_token		*tk;

	argc = 0;
	tk = tokens;
	while (tk)
	{
		if (tk->type == T_WORD)
			argc++;
		tk = tk->next;
	}
	cmd = malloc(sizeof(*cmd));
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	cmd->next = NULL;
	argc = 0;
	tk = tokens;
	while (tk)
	{
		if (tk->type == T_WORD)
			cmd->argv[argc++] = ft_strdup(tk->value);
		tk = tk->next;
	}
	cmd->argv[argc] = NULL;
	return (cmd);
}
