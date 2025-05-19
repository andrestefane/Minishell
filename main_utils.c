#include "Mini.h"
/* 
void	check_execute(t_token *token, char **env)
{
	t_command	*cmd;

	cmd = parse_single_command(token);
	if (!cmd)
		return ;
	if (is_builtin(cmd) && !has_redir(cmd) && !token_has_pipe(token)) //arreglar aqui
		execute_buitin(cmd, &env);
	else
		ft_execute(token, env);
	free_commands(cmd);
}
 */