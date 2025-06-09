/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_more_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:08:56 by alejaro2          #+#    #+#             */
/*   Updated: 2025/06/09 18:17:10 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	print_unclosed_error(char d)
{
	if (d == '\'')
		write(2, "minishell: syntax error: unclosed '\n", 37);
	else
		write(2, "minishell: syntax error: unclosed \"\n", 37);
}

int	is_token_char(char c)
{
	return (c && c != ' ' && c != '\t' && !ft_strchr("|<>", c));
}

int	handle_quote(t_tokenizer *tok, char *res, size_t *i, char d)
{
	while (tok->input[tok->pos] && tok->input[tok->pos] != d)
		res[(*i)++] = tok->input[tok->pos++];
	if (tok->input[tok->pos] != d)
		return (0);
	tok->pos++;
	return (1);
}

char	*extract_quoted_token(t_minishell *m)
{
	int		j;
	char	*val;
	char	quote_char;

	quote_char = m->tokenizer->input[m->tokenizer->pos];
	j = m->tokenizer->pos + 1;
	while (m->tokenizer->input[j] && m->tokenizer->input[j] != quote_char)
		j++;
	if (m->tokenizer->input[j] == '\0')
	{
		m->tokenizer->err = 1;
		return (NULL);
	}
	val = ft_substr(m->tokenizer->input, m->tokenizer->pos + 1, j
			- m->tokenizer->pos - 1);
	m->tokenizer->prev_type = T_WORD;
	m->tokenizer->pos = j + 1;
	return (val);
}

char	*extract_complex_token(t_minishell *m)
{
	char	*res;
	size_t	idx;

	if (m->tokenizer->input[m->tokenizer->pos] == '\''
		|| m->tokenizer->input[m->tokenizer->pos] == '"')
		return (get_next_token_part(m));
	res = malloc(ft_strlen(m->tokenizer->input) + 1);
	if (!res)
	{
		m->tokenizer->err = 1;
		return (NULL);
	}
	m->tokenizer->quote = Q_NONE;
	idx = 0;
	if (!fill_complex_res(m->tokenizer, res, &idx))
	{
		m->tokenizer->err = 1;
		free(res);
		return (NULL);
	}
	m->tokenizer->prev_type = T_WORD;
	return (res);
}
