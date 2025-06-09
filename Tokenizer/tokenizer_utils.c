/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:07:59 by alejaro2          #+#    #+#             */
/*   Updated: 2025/06/09 16:28:02 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

int	fill_tokens(t_minishell *minishell, char *input)
{
	int	success;

	success = 1;
	if (!init_tokenizer(minishell, input))
		return (0);
	success = tokenize_input(minishell);
	cleanup_tokenizer(minishell, success);
	return (success);
}

int	init_tokenizer(t_minishell *minishell, char *input)
{
	if (minishell->t_list)
	{
		free_t_list(minishell->t_list);
		minishell->t_list = NULL;
	}
	if (minishell->tokenizer)
		free(minishell->tokenizer);
	minishell->tokenizer = malloc(sizeof(t_tokenizer));
	if (!minishell->tokenizer)
		return (0);
	minishell->tokenizer->input = input;
	minishell->tokenizer->pos = 0;
	minishell->tokenizer->prev_type = T_WORD;
	minishell->tokenizer->quote = Q_NONE;
	minishell->tokenizer->err = 0;
	return (1);
}

int	tokenize_input(t_minishell *minishell)
{
	char	*val;

	while (!minishell->tokenizer->err)
	{
		val = extract_token(minishell);
		if (minishell->tokenizer->err || !val)
			break ;
		if (!create_token_and_detect_expansion(minishell, val))
		{
			free(val);
			return (0);
		}
		free(val);
	}
	return (1);
}

void	cleanup_tokenizer(t_minishell *minishell, int success)
{
	if (minishell->tokenizer)
	{
		if (minishell->tokenizer->err)
			success = 0;
		free(minishell->tokenizer);
		minishell->tokenizer = NULL;
	}
	if (!success)
	{
		free_t_list(minishell->t_list);
		minishell->t_list = NULL;
	}
}

int	fill_complex_res(t_tokenizer *tok, char *res, size_t *idx)
{
	char	d;

	while (tok->input[tok->pos] && is_token_char(tok->input[tok->pos]))
	{
		d = tok->input[tok->pos++];
		if (d == '\'' || d == '"')
		{
			if (!handle_quote(tok, res, idx, d))
			{
				print_unclosed_error(d);
				return (0);
			}
		}
		else
			res[(*idx)++] = d;
	}
	res[*idx] = '\0';
	return (1);
}
