#include "../Mini.h"

int	is_redir(t_redir *redir)
{
	return (redir->type == T_RED_IN || redir->type == T_RED_OUT
		|| redir->type == T_HEREDOC || redir->type == T_RED_APPEND);
}

void	apply_redirections(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (is_redir(redir) && ft_strchr("|'\"", redir->filename[0]))
			exit_with_error(SYNTAX_ERROR, 1, 2);
		apply_one_redirection(redir);
		redir = redir->next;
	}
}

void	apply_one_redirection(t_redir *redir)
{
	int	fd;

	if (redir->type == T_RED_IN || redir->type == T_HEREDOC)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == T_RED_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_with_error("Error opening file\n", 1, 2);
	if (redir->type == T_RED_IN || redir->type == T_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			exit_with_error("dup2 infile failed\n", 1, 2);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit_with_error("dup2 outfile failed\n", 1, 2);
	}
	close(fd);
}

void	add_redir_to_cmd(t_command *cmd, int type, const char *filename)
{
	t_redir	*new;
	t_redir	*last;

	new = malloc(sizeof(t_redir));
	if (!new)
		exit_with_error("malloc failed in redir\n", 1, 2);
	new->type = type;
	new->filename = ft_strdup(filename);
	new->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	has_redir_type(t_command *cmd, int type)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == type)
			return (1);
		r = r->next;
	}
	return (0);
}
