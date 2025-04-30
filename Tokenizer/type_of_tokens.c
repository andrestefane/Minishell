#include "../Mini.h"

void	expasion_and_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->num_tokens)
	{
		if (token->tokens[i].type == T_WORD)
		{
			if (token->tokens[i].value[0] == '~')
				token->tokens[i].expansion = TILDE_EXPANSION;
			else if (token->tokens[i].value[0] == '$')
			{
				if (token->tokens[i].value[1] == '?')
					token->tokens[i].expansion = EXIT_STATUS_EXPANSION;
				else
					token->tokens[i].expansion = VAR_EXPANSION;
			}
			else
				token->tokens[i].expansion = NO_EXPANSION;
		}
		else
			token->tokens[i].expansion = NO_EXPANSION;
		i++;
	}
}
