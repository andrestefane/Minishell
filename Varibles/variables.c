
#include "../Mini.h"


void	expand_token(t_token *token, t_minishell *mini)
{
	char	*var;

	if (token->expansion_type == VAR_EXPANSION)
	{
		var = env_value(token->value + 1, mini->env_list);
		if (token->value != NULL)
			free(token->value);
		if (var != NULL)
			token->value = ft_strdup(var);
		else
			token->value = ft_strdup("");
	}
	else if (token->expansion_type == EXIT_STATUS_EXPANSION)
	{
		if (token->value != NULL)
			free(token->value);
		ft_putstr("signal al comprobar ell valor del status: ", 2);
		ft_putnbr(mini->env_list->signal);
		ft_putstr("\n", 2);
		token->value = get_env_value("?", mini->env_list);
	}
}

