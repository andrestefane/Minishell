#include "../libft.h"

void	count_red_in(t_token *token, t_pipex *data)
{
	t_token	*tmp;

	tmp = token;
	data->count_fd = 0;
	data->count_heredoc = 0;
	while (tmp)
	{
		if (tmp->type == T_RED_IN && tmp->next && tmp->next->type == T_INFILE)
			data->count_fd++;
		else if (tmp->type == T_HEREDOC && tmp->next
			&& tmp->next->type == T_INFILE)
			data->count_heredoc++;
		tmp = tmp->next;
	}
	dprintf(STDOUT_FILENO, "Nº Infiles: %i\n", data->count_fd);
	dprintf(STDOUT_FILENO, "Nº Heredocs: %i\n", data->count_heredoc);
}
