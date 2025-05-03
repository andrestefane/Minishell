#include "../libft.h"

void	handle_input_redirection(t_token **tmp, t_pipex *data)
{
	if ((*tmp)->type == T_HEREDOC)
		data->heredoc = 1;
	else
		data->heredoc = 0;
	if ((*tmp)->next)
		data->limiter = (*tmp)->next->value;
	*tmp = (*tmp)->next;
	if (*tmp)
		*tmp = (*tmp)->next;
}

void	extract_commands(t_token *token, t_pipex *data)
{
	t_token	*tmp;
	int		j;

	tmp = token;
	j = 0;
	while (tmp)
	{
		if (tmp->type == T_WORD)
		{
			data->cmds[j] = ft_strdup(tmp->value);
			if (!data->cmds[j])
				free_struct(data, "Malloc ft_strdup\n", 1, 2);
			j++;
		}
		if (tmp->type == T_RED_OUT || tmp->type == T_RED_APPEND)
			break ;
		tmp = tmp->next;
	}
	data->cmds[j] = NULL;
	data->n_cmds = j;
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		free_struct(data, "Malloc pids\n", 1, 2);
}
