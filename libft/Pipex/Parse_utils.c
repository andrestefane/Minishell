#include "../libft.h"

void	parse_red_in(t_command *cmd, t_token **token)
{
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup((*token)->next->value);
	cmd->is_heredoc = 0;
	if (cmd->heredoc_file)
	{
		free(cmd->heredoc_file);
		cmd->heredoc_file = NULL;
	}
	*token = (*token)->next;
}

void	parse_red_out(t_command *cmd, t_token **token)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((*token)->next->value);
	*token = (*token)->next;
}

void	parse_red_append(t_command *cmd, t_token **token)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((*token)->next->value);
	cmd->append = 1;
	*token = (*token)->next;
}

void	parse_heredoc(t_command *cmd, t_token **token,
	t_pipex *data, int *index)
{
	if (cmd->heredoc_file)
		free(cmd->heredoc_file);
	handle_heredoc_in_command(cmd, (*token)->next->value, *index);
	cmd->is_heredoc = 1;
	data->count_heredoc++;
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	(*index)++;
	*token = (*token)->next;
}
