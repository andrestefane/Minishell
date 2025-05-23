#include "../Mini.h"

t_minishell	*init_minishell(void)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (NULL);
	minishell->env_list = NULL;
	minishell->token_list = NULL;
	minishell->command_list = NULL;
	minishell->pipex_data = NULL;
	return (minishell);
}
