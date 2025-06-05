#include "../Mini.h"


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

void	free_t_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
/* 		printf("HOLA REDIR: liberando filename = \"%s\", ptr = %p\n",
				redir->filename, (void *)redir->filename); */
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_command_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->redirs)
			free_redir_list(cmd->redirs);
		if (cmd->argv)
		{
			ft_freedoom(cmd->argv);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd->heredoc_file);
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
