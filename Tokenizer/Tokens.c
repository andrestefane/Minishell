/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:28:37 by astefane          #+#    #+#             */
/*   Updated: 2025/05/26 17:35:45 by alejaro2         ###   ########.fr       */
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

t_token	*add_token(t_token **head, char *value, t_token_type type,
		t_token_quote quote)
{
	t_token	*new_node;
	t_token	*current;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(value);
	new_node->type = type;
	new_node->quote = quote;
	new_node->expansion_type = NO_EXPANSION;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
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

char	*extract_word(t_tokenizer *tok, t_token_type *type)
{
	int	start;

	start = tok->pos;
	while (is_word_char(tok->input[tok->pos]))
		tok->pos++;
	if (tok->pos == start)
		return (NULL);
	*type = T_WORD;
	return (ft_substr(tok->input, start, tok->pos - start));
}

char	*extract_token(t_tokenizer *tok, t_token_type *type,
		t_token_quote *quote)
{
	while (tok->input[tok->pos] == ' ' || tok->input[tok->pos] == '\t')
		tok->pos++;
	if (tok->input[tok->pos] == '\0')
		return (NULL);
	if (extract_metachar(tok, type, quote))
		return (ft_strdup(""));
	return (extract_complex_token(tok, type, quote));
}
