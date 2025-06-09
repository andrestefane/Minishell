/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:41:29 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 15:41:30 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	expand_token(t_token *token, t_minishell *mini)
{
	char	*expanded;

	if (token->quote == Q_SINGLE)
		return ;
	expanded = expand_env_in_str(token->value, mini);
	free(token->value);
	token->value = expanded;
}
