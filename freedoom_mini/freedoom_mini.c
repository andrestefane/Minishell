#include "../Mini.h"

void	free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->env_list)
		free_env_list(minishell->env_list);
	if (minishell->t_list)
		free_t_list(minishell->t_list);
	if (minishell->command_list
		&& minishell->pipex_data
		&& minishell->command_list != minishell->pipex_data->commands)
		free_command_list(minishell->command_list);
	if (minishell->pipex_data)
		free_pipex_data(minishell->pipex_data);
	free(minishell);
}
