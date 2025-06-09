/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_more_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:05:31 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 16:53:42 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

t_token	*check_expansion(t_minishell *minishell, char *val)
{
	t_token	*new_token;

	new_token = add_token(minishell, val);
	if (!new_token)
		return (NULL);
	new_token->type = minishell->tokenizer->prev_type;
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
