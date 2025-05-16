
#include "../Mini.h"

void	parse_red_in(t_command *cmd, t_token **token)
{
	if (!(*token)->next)
		exit_with_error("syntax error: no infile\n", 1, 2);
	else if ((*token)->type != T_RED_IN)
		exit_with_error("syntax error: no infile\n", 1, 2);
	add_redir_to_cmd(cmd, T_RED_IN, (*token)->next->value);
	*token = (*token)->next;
}

void	parse_red_out(t_command *cmd, t_token **token)
{
	if (!(*token)->next)
		exit_with_error("syntax error: no outfile\n", 1, 2);
	add_redir_to_cmd(cmd, T_RED_OUT, (*token)->next->value);
	*token = (*token)->next;
}

void	parse_red_append(t_command *cmd, t_token **token)
{
	if (!(*token)->next)
		exit_with_error("syntax error: no outfile\n", 1, 2);
	add_redir_to_cmd(cmd, T_RED_APPEND, (*token)->next->value);
	cmd->append = 1;
	*token = (*token)->next;
}

void	parse_heredoc(t_command *cmd, t_token **token,
	t_pipex *data, int *index)
{
	char	*filename;

	if (!(*token)->next || !(*token)->next->value)
		exit_with_error("heredoc: missing limiter\n", 1, 2);
	filename = handle_heredoc_in_command(cmd, (*token)->next->value, *index);
	add_redir_to_cmd(cmd, T_HEREDOC, filename);
	cmd->is_heredoc = 1;
	data->count_heredoc++;
	(*index)++;
	*token = (*token)->next;
}
