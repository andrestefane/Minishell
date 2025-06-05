
#include "../Mini.h"

t_command	*parse_commands(t_minishell *mini)
{
	t_command	*head;
	t_command	*curr;
	t_token		*token;
	int			heredoc_index;

	heredoc_index = 0;
	head = NULL;
	curr = NULL;
	token = mini->t_list;
	while (token)
	{
		if (!curr)
		{
			curr = init_new_command();
			add_command_to_list(&head, curr);
		}
		process_token(&curr, &token, mini, &heredoc_index);
		token = token->next;
	}
	return (head);
}

void	process_token(t_command **curr, t_token **token,
	t_minishell *mini, int *index)
{
	t_pipex	*data;

	data = mini->pipex_data;
	if ((*token)->type == T_WORD)
{
	if ((*token)->expansion_type != NO_EXPANSION)
		expand_token(*token, mini);
	if ((*token)->value[0] == '\0' && (*token)->quote != Q_SINGLE)
	{
		return ;
	}
	add_arg_to_command(*curr, (*token)->value);
}
	else if ((*token)->type == T_RED_IN && (*token)->next)
		parse_red_in(*curr, token, data);
	else if ((*token)->type == T_RED_OUT && (*token)->next)
		parse_red_out(*curr, token, data);
	else if ((*token)->type == T_RED_APPEND && (*token)->next)
		parse_red_append(*curr, token, data);
	else if ((*token)->type == T_HEREDOC && (*token)->next)
		parse_heredoc(*curr, token, data, index);
	else if ((*token)->type == T_PIPE)
		*curr = NULL;
}
