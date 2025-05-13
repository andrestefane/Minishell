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


char	*get_next_token_part(t_tokenizer *tok,
				t_token_type *type, t_token_quote *current_quote)
{
	char	*temp;

	if (tok->input[tok->pos] == '\'' || tok->input[tok->pos] == '"')
		temp = extract_quoted_token(tok, type, current_quote);
	else
	{
		temp = extract_word(tok, type);
		*current_quote = Q_NONE;
	}
	return (temp);
}
