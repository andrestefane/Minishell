/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:07:19 by alejaro2          #+#    #+#             */
/*   Updated: 2025/06/09 16:07:22 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

static int	is_word_char(char c)
{
	if (c == '\0')
		return (0);
	if (c == ' ' || c == '\t')
		return (0);
	if (c == '|' || c == '<' || c == '>')
		return (0);
	if (c == '\'' || c == '"')
		return (0);
	return (1);
}

t_token	*add_token(t_minishell *minishell, char *value)
{
	t_token	*new_node;
	t_token	*current;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(value);
	new_node->type = minishell->tokenizer->prev_type;
	new_node->quote = Q_NONE;
	new_node->expansion_type = NO_EXPANSION;
	new_node->next = NULL;
	if (minishell->t_list == NULL)
	{
		minishell->t_list = new_node;
	}
	else
	{
		current = minishell->t_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (new_node);
}

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

char	*extract_word(t_minishell *m)
{
	int		start;
	char	*word;

	start = m->tokenizer->pos;
	while (is_word_char(m->tokenizer->input[m->tokenizer->pos]))
		m->tokenizer->pos++;
	if (m->tokenizer->pos == start)
		return (NULL);
	word = ft_substr(m->tokenizer->input, start, m->tokenizer->pos - start);
	return (word);
}

char	*extract_token(t_minishell *m)
{
	char	*val;

	while (m->tokenizer->input[m->tokenizer->pos] == ' '
		|| m->tokenizer->input[m->tokenizer->pos] == '\t')
		m->tokenizer->pos++;
	if (m->tokenizer->input[m->tokenizer->pos] == '\0')
		return (NULL);
	val = extract_metachar(m);
	if (val)
		return (val);
	return (extract_complex_token(m));
}
