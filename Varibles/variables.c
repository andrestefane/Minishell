
#include "../Mini.h"


void	expand_token(t_token *token, t_minishell *mini)
{
	char	*var;

	if (token->expansion_type == VAR_EXPANSION)
	{
		var = env_value(token->value + 1, mini->env_list);
	}
}

