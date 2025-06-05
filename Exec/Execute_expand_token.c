#include "../Mini.h"

void	expand_tokens(t_token *t_list)
{
	t_token	*curr;
	char	*expanded;

	cur = t_list;
	while (curr)
	{
		if (curr->quote != Q_SINGLE
			&& curr->expansion_type == EXIT_STATUS_EXPANSION)
		{
			free(curr->value);
			curr->value = ft_itoa(g_exit_status);
			curr->expansion_type = NO_EXPANSION;
		}
	}
}
