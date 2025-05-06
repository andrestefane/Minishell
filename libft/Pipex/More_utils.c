#include "../libft.h"

t_command	*parse_commands(t_token *token)
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
		if (token->type == T_WORD)
			add_arg_to_command(curr, token->value);
		if (token->type == T_RED_IN && token->next)
		{
			if (curr->infile)
				free(curr->infile);
			curr->infile = ft_strdup(token->next->value);
			curr->is_heredoc = 0; // sobrescribe heredoc si había
			if (curr->heredoc_file)
			{
				free(curr->heredoc_file);
				curr->heredoc_file = NULL;
			}
			token = token->next;
		}
		else if (token->type == T_RED_OUT && token->next)
		{
			curr->outfile = ft_strdup(token->next->value);
			token = token->next;
		}
		else if (token->type == T_RED_APPEND && token->next)
		{
			curr->outfile = ft_strdup(token->next->value);
			curr->append = 1;
			token = token->next;
		}
		else if (token->type == T_HEREDOC && token->next)
		{
			if (curr->heredoc_file)
				free(curr->heredoc_file);
			handle_heredoc_in_command(curr, token->next->value, heredoc_index);
			curr->is_heredoc = 1;
			if (curr->infile)
			{
				free(curr->infile);
				curr->infile = NULL;
			}
			heredoc_index++;
			token = token->next;
		}
		else if (token->type == T_PIPE)
			curr = NULL;
		token = token->next;
	}
	return (head);
}

void	add_command_to_list(t_command **head, t_command *new_cmd)
{
	t_command	*tmp;

	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

void	add_arg_to_command(t_command *cmd, char *arg)
{
	int		count;
	int		i;
	char	**new_argv;

	count = 0;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		exit_with_error("Error malloc argv\n", 1, 2);
	while (i < count)
	{
		new_argv[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	new_argv[count] = ft_strdup(arg);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	handle_heredoc_in_command(t_command *cmd, char *limiter, int index)
{
	char	*filename;

	filename = get_filename(index);
	if (!filename)
		exit_with_error("malloc filename failed\n", 1, 2);
	if (here_doc(limiter, filename) == -1)
		free_and_error(filename, "Error reading heredoc\n", 1, 2);
	cmd->is_heredoc = 1;
	cmd->heredoc_file = filename;
}

t_command	*init_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->heredoc_file = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	count_commands_list(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

char	**split_command(char *cmd)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_freedoom(cmd_split);
		return (NULL);
	}
	return (cmd_split);
}
