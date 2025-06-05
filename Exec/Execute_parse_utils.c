
#include "../Mini.h"

void	parse_red_in(t_minishell *mini, t_token **token)
{
	if (!(*token)->next || (*token)->type != T_RED_IN)
	{
		if (mini->pipex_data)
		{
			free_pipex_data(mini->pipex_data);
			mini->pipex_data = NULL;
		}
		mini->curr->redirs = NULL;
		exit_with_error("syntax error: no infile\n", 1, 2);
	}
	add_redir_to_cmd(mini, T_RED_IN, (*token)->next->value);
	*token = (*token)->next;
}

void	parse_red_out(t_minishell *mini, t_token **token)
{
	if (!(*token)->next)
	{
		if (mini->pipex_data)
		{
			free_pipex_data(mini->pipex_data);
			mini->pipex_data = NULL;
		}
		mini->curr->redirs = NULL;
		exit_with_error("syntax error: no outfile\n", 1, 2);
	}
	add_redir_to_cmd(mini->curr, T_RED_OUT, (*token)->next->value);
	*token = (*token)->next;
}

void	parse_red_append(t_minishell *mini, t_token **token)
{
	if (!(*token)->next)
	{
		if (mini->pipex_data)
		{
			free_pipex_data(mini->pipex_data);
			mini->pipex_data = NULL;
		}
		mini->curr->redirs = NULL;
		exit_with_error("syntax error: no outfile\n", 1, 2);
	}
	add_redir_to_cmd(mini->curr, T_RED_APPEND, (*token)->next->value);
	mini->curr->append = 1;
	*token = (*token)->next;
}

void	parse_heredoc(t_minishell *mini, t_token **token, int *index)
{
	char	*filename;

	if (!(*token)->next || !(*token)->next->value)
	{
		if (mini->pipex_data)
		{
			free_pipex_data(mini->pipex_data);
			mini->pipex_data = NULL;
		}
		mini->curr->redirs = NULL;
		exit_with_error("heredoc: missing limiter\n", 1, 2);
	}
	filename = handle_heredoc_in_command(mini->curr, (*token)->next->value,
			*index);
	if (!filename)
	{
		g_status = 130;
		mini->curr->is_heredoc = 0;
		return ;
	}
	add_redir_to_cmd(mini->curr, T_HEREDOC, filename);
	mini->curr->is_heredoc = 1;
	mini->pipex_data->count_heredoc++;
	(*index)++;
	*token = (*token)->next;
}
