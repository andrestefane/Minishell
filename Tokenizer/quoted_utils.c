#include "../Mini.h"

int	is_empty_token(char *temp)
{
	int	i;

	if (!temp || temp[0] == '\0')
		return (1);
	i = 0;
	while (temp[i])
	{
		if (temp[i] != ' ' && temp[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}


char	*get_next_token_part(t_minishell *m)
{
	char	*temp;

	if (m->t_list->tok->input[m->t_list->tok->pos] == '\''
		|| m->t_list->tok->input[m->t_list->tok->pos] == '"')
	{
		temp = extract_quoted_token(m);
	}
	else
	{
		temp = extract_word(m);
		m->t_list->quote = Q_NONE;
	}
	return (temp);
}

