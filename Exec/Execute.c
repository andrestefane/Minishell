/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:05:43 by astefane          #+#    #+#             */
/*   Updated: 2025/04/29 20:18:39 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	check_type(t_token *token, char **envir)
{
	int	i;
	int	has_input;
	int	has_pipe;
	int	has_output;

	i = 0;
	has_input = 0;
	has_pipe = 0;
	has_output = 0;
	while (i < token->num_tokens)
	{
		if (token->tokens[i].type == T_RED_IN
			|| token->tokens[i].type == T_HEREDOC)
			has_input = 1;
		else if (token->tokens[i].type == T_PIPE)
			has_pipe = 1;
		else if (token->tokens[i].type == T_RED_OUT
			|| token->tokens[i].type == T_RED_APPEND)
			has_output = 1;
		i++;
	}
	if ((has_input && has_pipe && has_output )|| (has_input && has_output))
		pipex(token, envir);
}
