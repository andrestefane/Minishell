#include "../Mini.h"

char	*expand_env_in_str(char *src, t_minishell *mini)
{
	char	*res;
	int		i;
	int		start;

	res = ft_strdup("");
	i = 0;
	while (src[i])
	{
		if (src[i] == '$')
			append_var(&res, src, &i, mini);
		else
		{
			start = i;
			while (src[i] && src[i] != '$')
				i++;
			append_literal(&res, src + start, i - start);
		}
	}
	return (res);
}

void	append_var(char **res, char *src, int *i, t_minishell *mini)
{
	char	*var;
	char	*tmp;
	char	*val;
	int		len;
	int		j;

	j = *i + 1;
	if (src[j] == '?')
	{
		val = get_env_value("?", mini->env_list);
		if (val)
		{
			tmp = *res;
			*res = ft_strjoin(*res, val);
			free(tmp);
		}
		else
		{
			tmp = *res;
			*res = ft_strjoin(*res, "");
			free(tmp);
		}
		*i += 2;
		free(val);
		return ;
	}
	while (src[j] && (ft_isalnum(src[j]) || src[j] == '_'))
		j++;
	len = j - (*i + 1);
	if (len > 0)
	{
		var = ft_substr(src, *i + 1, len);
		val = env_value(var, mini->env_list);
		if (val)
			*res = ft_strjoin(*res, val);
		else
			*res = ft_strjoin(*res, "");
		free(var);
	}
	else
		*res = ft_strjoin(*res, "$");
	*i = j;
}

void	append_literal(char **res, char *src, int len)
{
	char	*lit;

	lit = ft_substr(src, 0, len);
	*res = ft_strjoin(*res, lit);
	free(lit);
}

t_token	*create_token_and_detect_expansion(t_minishell *minishell, char *val)
{
	t_token	*new_token;

	new_token = add_token(minishell, val);
	if (!new_token)
		return (NULL);

	// ← Importante: asignar tipo desde el tokenizer
	new_token->type = minishell->tokenizer->prev_type;

	// Detectar expansión
	if (new_token->type == T_WORD && new_token->value[0] == '$')
	{
		if (new_token->value[1] == '?' && new_token->value[2] == '\0')
			new_token->expansion_type = EXIT_STATUS_EXPANSION;
		else
			new_token->expansion_type = VAR_EXPANSION;
	}
	else
		new_token->expansion_type = NO_EXPANSION;

	return (new_token);
}
