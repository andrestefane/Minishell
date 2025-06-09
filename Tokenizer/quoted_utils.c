/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:34:29 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 15:34:30 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

int	is_empty_token(char *temp)
{
	int	i;

	if (!temp || temp[0] == '\0')
		return (1);
	i = 0;
	while (temp[i])
	{
		if (temp[i] != ' ' && temp[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*get_next_token_part(t_minishell *m)
{
	char	*temp;

	if (m->tokenizer->input[m->tokenizer->pos] == '\''
		|| m->tokenizer->input[m->tokenizer->pos] == '"')
	{
		temp = extract_quoted_token(m);
	}
	else
	{
		temp = extract_word(m);
		m->tokenizer->quote = Q_NONE;
	}
	return (temp);
}
