
#include "../Mini.h"

/* void	expand_token(t_token *token, char **env)
{
	int	i;

	i = 0;
	while (i < token->num_tokens)
	{
		if (token->tokens[i].type == T_WORD)
		{
			if (!is_simple_quotes(token->tokens[i].value))
			{
				if (token->tokens[i].expansion == TILDE_EXPANSION)
					expand_tilde(&token->tokens[i], env);
				else if (token->tokens[i].expansion == VAR_EXPANSION
					|| token->tokens[i].expansion == EXIT_STATUS_EXPANSION)
					expand_variable(&token->tokens[i], env);
			}
		}
		i++;
	}
} */