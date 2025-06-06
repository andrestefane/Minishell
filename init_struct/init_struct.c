#include "../Mini.h"

t_minishell	init_minishell(void)
{
	t_minishell	minishell;

	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.env_list = NULL;
	minishell.t_list = NULL;
	minishell.command_list = NULL;
	minishell.pipex_data = NULL;
	minishell.head = NULL;
	minishell.tmp = NULL;
	minishell.tokenizer = NULL;
	minishell.curr_token = NULL;
	minishell.new_token = NULL;
	minishell.new_node = NULL;
	minishell.current = NULL;
	return (minishell);
}
