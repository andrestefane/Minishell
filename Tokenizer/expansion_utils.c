#include "../Mini.h"

t_token	*create_token_and_detect_expansion(t_token **list, char *val, t_token_type type, t_token_quote quote)
{
	t_token *new_token;

	new_token = add_token(list, val, type, quote);
	if (new_token && new_token->type == T_WORD && new_token->value[0] == '$')
	{
		if (new_token->value[1] == '?' && new_token->value[2] == '\0')
			new_token->expansion_type = EXIT_STATUS_EXPANSION;
		else
			new_token->expansion_type = VAR_EXPANSION;
	}
	return (new_token);
}
