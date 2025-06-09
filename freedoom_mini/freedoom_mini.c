/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedoom_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:05:28 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 14:25:37 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	free_minishell(t_minishell *m)
{
	if (!m)
		return ;
	if (m->env_list)
		(free_env_list(m->env_list), m->env_list = NULL);
	if (m->t_list)
		(free_t_list(m->t_list), m->t_list = NULL);
	if (m->pipex_data && m->command_list)
		(free_pipex_data(m->pipex_data), m->pipex_data = NULL);
	if (m->tokenizer)
	{
		free_tokenizer(m->tokenizer);
		m->tokenizer = NULL;
	}
	ft_freedoom(m->envir_execve);
	ft_freedoom(m->paths_execve);
	m->curr_token = NULL;
	m->new_token = NULL;
	m->new_node = NULL;
	m->current = NULL;
	m->head = NULL;
	m->tmp = NULL;
	m->curr = NULL;
}

void	free_tokenizer(t_tokenizer *tok)
{
	if (!tok)
		return ;
	free(tok);
}

void	free_and_reset_token_list(t_minishell *mini)
{
	if (!mini)
		return ;
	if (mini->t_list)
	{
		free_t_list(mini->t_list);
		mini->t_list = NULL;
	}
}
