#include "../Mini.h"

t_env	*init_env_list(char *name, char *value, int exported)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = name;
	env->value = value;
	env->exported = exported;
	env->name = NULL;
	return (env);
}

t_token	*init_token(char *value, t_token_type type,
		t_token_quote quote, t_expansion_type exp)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->quote = quote;
	token->expansion_type = exp;
	token->next = NULL;
	return (token);
}

t_redir	*init_redir(int type, const char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
		return (free(redir), NULL);
	redir->next = NULL;
	return (redir);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->heredoc_file = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_pipex	*init_pipex(void)
{
	t_pipex	*px;

	px = malloc(sizeof(t_pipex));
	if (!px)
		return (NULL);
	px->prev_fd = -1;
	px->count_heredoc = 0;
	px->n_cmds = 0;
	px->builtins = 0;
	px->pid = NULL;
	px->commands = NULL;
	return (px);
}
