/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_redirs_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:38:39 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 14:38:40 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

int	has_redir(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (is_redir(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	token_has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == T_PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}
