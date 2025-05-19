#include "../Mini.h"

static t_command	*allocate_command(t_token *tokens)
{
	int			argc;
	t_token		*tk;
	t_command	*cmd;

	argc = 0;
	tk = tokens;
	while (tk)
	{
		if (tk->type == T_WORD)
			argc++;
		tk = tk->next;
	}
	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		exit_with_error("malloc failed\n", 1, 1);
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		exit_with_error("malloc failed\n", 1, 1);
	cmd->next = NULL;
	return (cmd);
}
t_command	*parse_single_command(t_token *tokens)
{
	t_command *cmd = allocate_command(tokens);
	t_token *tk = tokens;
	int i = 0;

	while (tk)
	{
		if (tk->type == T_WORD)
			cmd->argv[i++] = ft_strdup(tk->value);
		tk = tk->next;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}
