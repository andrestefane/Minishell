#include "../Mini.h"

void	free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
	/* free_env_list(minishell->env_list);
	minishell->env_list = NULL; */
	free_token_list(minishell->token_list);
	minishell->token_list = NULL;
	if (minishell->command_list
		&& minishell->command_list != minishell->pipex_data->commands)
	{
		free_command_list(minishell->command_list);
		minishell->command_list = NULL;
	}
	free_pipex_data(minishell->pipex_data);
	minishell->pipex_data = NULL;
}
