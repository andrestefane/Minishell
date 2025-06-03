
#include "../Mini.h"

void	parse_red_in(t_command *cmd, t_token **token, t_pipex *data)
{
	if (!(*token)->next || (*token)->type != T_RED_IN)
	{
		if (data)
		{
			free_pipex_data(data);
			data = NULL;
			cmd->redirs = NULL;
		}
		exit_with_error("syntax error: no infile\n", 1, 2);
	}
	else if ((*token)->type != T_RED_IN)
		exit_with_error("syntax error: no infile\n", 1, 2);
	add_redir_to_cmd(cmd, T_RED_IN, (*token)->next->value);
	*token = (*token)->next;
}

void	parse_red_out(t_command *cmd, t_token **token, t_pipex *data)
{
	if (!(*token)->next)
	{
		if (data)
		{
			free_pipex_data(data);
			data = NULL;
			cmd->redirs = NULL;
		}
		exit_with_error("syntax error: no outfile\n", 1, 2);
	}
	add_redir_to_cmd(cmd, T_RED_OUT, (*token)->next->value);
	*token = (*token)->next;
}

void	parse_red_append(t_command *cmd, t_token **token, t_pipex *data)
{
	if (!(*token)->next)
	{
		if (data)
		{
			free_pipex_data(data);
			data = NULL;
			cmd->redirs = NULL;
		}
		exit_with_error("syntax error: no outfile\n", 1, 2);
	}
	add_redir_to_cmd(cmd, T_RED_APPEND, (*token)->next->value);
	cmd->append = 1;
	*token = (*token)->next;
}

void	parse_heredoc(t_command *cmd, t_token **token,
	t_pipex *data, int *index)
{
	char	*filename;

	if (!(*token)->next || !(*token)->next->value)
	{
		if (data)
		{
			free_pipex_data(data);
			data = NULL;
			cmd->redirs = NULL;
		}
		exit_with_error("heredoc: missing limiter\n", 1, 2);
	}
	filename = handle_heredoc_in_command(cmd, (*token)->next->value, *index);
	if (!filename)
	{
		g_status = 130;
		cmd->is_heredoc = 0;
		return ;
		if (data)
		{
			free_pipex_data(data);
			data = NULL;
			cmd->redirs = NULL;
		}
	}
	add_redir_to_cmd(cmd, T_HEREDOC, filename);
	cmd->is_heredoc = 1;
	data->count_heredoc++;
	(*index)++;
	*token = (*token)->next;

}
