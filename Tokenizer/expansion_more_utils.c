/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_more_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:05:31 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 15:28:32 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

// void	handle_question_mark(char **res, int *i, t_minishell *mini)
// {
// 	char	*val;
// 	char	*tmp;

// 	val = get_env_value("?", mini->env_list);
// 	tmp = *res;
// 	if (val)
// 		*res = ft_strjoin(*res, val);
// 	else
// 		*res = ft_strjoin(*res, "");
// 	free(tmp);
// 	*i += 2;
// 	free(val);
// }

// void	handle_variable(char **res, char *var, t_minishell *mini)
// {
// 	char	*val;

// 	val = env_value(var, mini->env_list);
// 	if (val)
// 		*res = ft_strjoin(*res, val);
// 	else
// 		*res = ft_strjoin(*res, "");
// 	free(var);
// }

// void	get_variable_length(char *src, int *i, int *len)
// {
// 	int	j;

// 	j = *i + 1;
// 	while (src[j] && (ft_isalnum(src[j]) || src[j] == '_'))
// 		j++;
// 	*len = j - (*i + 1);
// }

// void	append_var(char **res, char *src, int *i, t_minishell *mini)
// {
// 	int		len;
// 	char	*var;

// 	if (src[*i + 1] == '?')
// 	{
// 		handle_question_mark(res, i, mini);
// 		return ;
// 	}
// 	get_variable_length(src, i, &len);
// 	if (len > 0)
// 	{
// 		var = ft_substr(src, *i + 1, len);
// 		handle_variable(res, var, mini);
// 	}
// 	else
// 	{
// 		*res = ft_strjoin(*res, "$");
// 	}
// }
