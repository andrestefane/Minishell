
#include "../Mini.h"

t_command	*parse_commands(t_token *token, t_pipex *data)
{
	t_command	*head;
	t_command	*curr;
	int			heredoc_index;

	heredoc_index = 0;
	head = NULL;
	curr = NULL;
	while (token)
	{
		if (!curr)
		{
			curr = init_new_command();
			add_command_to_list(&head, curr);
		}
		process_token(&curr, &token, data, &heredoc_index);
		token = token->next;
	}
	return (head);
}

void	process_token(t_command **curr, t_token **token,
	t_pipex *data, int *index)
{
	if ((*token)->type == T_WORD)
		add_arg_to_command(*curr, (*token)->value);
	else if ((*token)->type == T_RED_IN && (*token)->next)
		parse_red_in(*curr, token);
	else if ((*token)->type == T_RED_OUT && (*token)->next)
		parse_red_out(*curr, token);
	else if ((*token)->type == T_RED_APPEND && (*token)->next)
		parse_red_append(*curr, token);
	else if ((*token)->type == T_HEREDOC && (*token)->next)
		parse_heredoc(*curr, token, data, index);
	else if ((*token)->type == T_PIPE)
		*curr = NULL;
}

void	apply_redirections(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
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
