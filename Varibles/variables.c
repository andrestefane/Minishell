
#include "../Mini.h"

// void	expand_token(t_token *token, t_minishell *mini)
// {
// 	char	*var;
// 	// printf("DEBUG: expand_token value=[%s], quote=%d\n", token->value, token->quote);
// 	if (token->quote == Q_SINGLE)
// 		return ;
// 	if (token->expansion_type == VAR_EXPANSION)
// 	{
// 		var = env_value(token->value + 1, mini->env_list);
// 		if (token->value != NULL)
// 			free(token->value);
// 		if (var != NULL)
// 			token->value = ft_strdup(var);
// 		else
// 			token->value = ft_strdup("");
// 	}
// 	else if (token->expansion_type == EXIT_STATUS_EXPANSION)
// 	{
// 		if (token->value != NULL)
// 			free(token->value);
// 		token->value = get_env_value("?", mini->env_list);
// 	}
// }

void	expand_token(t_token *token, t_minishell *mini)
{
	char	*expanded;

	if (token->quote == Q_SINGLE)
		return ;
	expanded = expand_env_in_str(token->value, mini);
	free(token->value);
	token->value = expanded;
}
