
#include "../Mini.h"

t_command	*parse_commands(t_minishell *mini)
{
	int	heredoc_index;

	heredoc_index = 0;
	mini->head = NULL;
	mini->curr = NULL;
	while (mini->t_list)
	{
		if (!mini->curr)
		{
			mini->curr = init_new_command();
			add_command_to_list(mini);
		}
		process_token(mini, &heredoc_index);
		mini->t_list = mini->t_list->next;
	}
	return (mini->head);
}

void	process_token(t_minishell *mini, int *index)
{
	t_token	*token;

	token = mini->t_list;
	if (token->type == T_WORD)
	{
		if (token->expansion_type != NO_EXPANSION)
			expand_token(token, mini);
		if (token->value[0] == '\0' && token->quote != Q_SINGLE)
			return ;
		add_arg_to_command(mini, token->value);
	}
	else if (token->type == T_RED_IN && token->next)
		parse_red_in(mini, &mini->t_list);
	else if (token->type == T_RED_OUT && token->next)
		parse_red_out(mini, &mini->t_list);
	else if (token->type == T_RED_APPEND && token->next)
		parse_red_append(mini, &mini->t_list);
	else if (token->type == T_HEREDOC && token->next)
		parse_heredoc(mini, &mini->t_list, index);
	else if (token->type == T_PIPE)
		mini->curr = NULL;
}
