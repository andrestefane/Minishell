
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
	{
/* 		if ((*token)->type == T_DOLLAR && (*token)->next->type == T_QUESTION
			|| (*token)->type == T_DOLLAR)
		{
			free((*token)->value);
			(*token)->value = ft_itoa(g_status);
		} */
		add_arg_to_command(*curr, (*token)->value);
	}
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
