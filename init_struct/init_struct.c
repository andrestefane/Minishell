#include "../Mini.h"

t_minishell	init_minishell(void)
{
	t_minishell	minishell;

	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.env_list = NULL;
	minishell.t_list = NULL;
	minishell.command_list = NULL;
	minishell.pipex_data = NULL;
	return (minishell);
}
