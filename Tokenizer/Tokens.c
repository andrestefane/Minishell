/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:28:37 by astefane          #+#    #+#             */
/*   Updated: 2025/05/07 13:32:52 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	add_token(t_token **head, char *value, t_token_type type, t_token_quote quote)
{
	t_token	*new_node;
	t_token	*current;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->value = ft_strdup(value);
	new_node->type = type;
	new_node->quote = quote;
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

/* tokenizer_utils.c */

char	*extract_word(t_tokenizer *tok, t_token_type *type)
{
	int	start;

	start = tok->pos;
	while (tok->input[tok->pos] && tok->input[tok->pos] != ' '
		&& tok->input[tok->pos] != '\t' && tok->input[tok->pos] != '|'
		&& tok->input[tok->pos] != '<' && tok->input[tok->pos] != '>')
	{
		tok->pos++;
	}
	if (tok->pos == start)
		return (NULL);
	*type = T_WORD;
	return (ft_substr(tok->input, start, tok->pos - start));
}

char	*extract_token(t_tokenizer *tok, t_token_type *type,
		t_token_quote *quote)
{
	char	*val;

	while (tok->input[tok->pos] == ' ' || tok->input[tok->pos] == '\t')
		tok->pos++;
	if (tok->input[tok->pos] == '\0')
		return (NULL);
	if (tok->input[tok->pos] == '\'' || tok->input[tok->pos] == '"')
	{
		val = extract_quoted_token(tok, type, quote);
		if (!val)
			tok->err = 1;
		return (val);
	}
	if (extract_metachar(tok, type, quote))
		return (ft_strdup(""));
	*quote = Q_NONE;
	val = extract_word(tok, type);
	return (val);
}
