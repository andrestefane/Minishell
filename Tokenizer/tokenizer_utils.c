#include "../Mini.h"

int	fill_tokens(t_token *list, int *token_idx)
{
	int				i;
	t_token_type	type;
	char			*token;

	i = 0;
	while (list->input[i])
	{
		token = extract_token(list->input, &i, &type);
		if (!token)
			return (0);
		if (*token)
		{
			list->tokens[*token_idx].value = token;
			list->tokens[*token_idx].type = type;
			(*token_idx)++;
		}
		else
			free(token);
	}
	return (1);
}

int	split_tokens(t_token *list)
{
	int	token_idx;

	if (!list || !list->input)
		return (0);
	token_idx = 0;
	list->tokens = malloc(sizeof(t_single_token) * (list->num_tokens + 1));
	if (!list->tokens)
		return (0);
	if (!fill_tokens(list, &token_idx))
	{
		free(list->tokens);
		return (0);
	}
	list->tokens[token_idx].value = NULL;
	list->num_tokens = token_idx;
	return (1);
}

void	free_token_list(t_token *list)
{
	int	i;

	if (!list)
		return ;
	if (list->input)
		free(list->input);
	if (list->tokens)
	{
		i = 0;
		while (list->tokens[i].value)
		{
			free(list->tokens[i].value);
			i++;
		}
		free(list->tokens);
	}
	free(list);
}
