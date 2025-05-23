#include "Mini.h"

void	free_env_list(t_env	*env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = tmp->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_command_list(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd->heredoc_file);
		free_redir_list(cmd->redirs);
		free(cmd);
		cmd = tmp;
	}
}

void	free_pipex_data(t_pipex *data)
{
	if (!data)
		return ;
	if (data->pid)
		free(data->pid);
	if (data->commands)
		free_command_list(data->commands);
	free(data);
}
