/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:50:21 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 16:47:54 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

static void	append_exit_code(char **res, int *i, t_minishell *mini)
{
	char	*val;
	char	*tmp;

	val = get_env_value("?", mini->env_list);
	tmp = *res;
	if (val)
		*res = ft_strjoin(*res, val);
	else
		*res = ft_strjoin(*res, "");
	free(tmp);
	free(val);
	*i += 2;
}

static void	append_variable(char **res, char *src, int *i, t_minishell *mini)
{
	char	*var;
	char	*val;
	int		j;
	int		len;

	j = *i + 1;
	while (src[j] && (ft_isalnum(src[j]) || src[j] == '_'))
		j++;
	len = j - (*i + 1);
	if (len > 0)
	{
		var = ft_substr(src, *i + 1, len);
		val = env_value(var, mini->env_list);
		free(var);
		if (val)
			*res = ft_strjoin(*res, val);
		else
			*res = ft_strjoin(*res, "");
	}
	else
		*res = ft_strjoin(*res, "$");
	*i = j;
}

void	append_var(char **res, char *src, int *i, t_minishell *mini)
{
	if (src[*i + 1] == '?')
		append_exit_code(res, i, mini);
	else
		append_variable(res, src, i, mini);
}

void	append_literal(char **res, char *src, int len)
{
	char	*lit;

	lit = ft_substr(src, 0, len);
	*res = ft_strjoin(*res, lit);
	free(lit);
}
