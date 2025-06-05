/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:28:37 by astefane          #+#    #+#             */
/*   Updated: 2025/06/05 19:24:55 by alejaro2         ###   ########.fr       */
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
	new_node->type = minishell->t_list->type;
	new_node->quote = minishell->t_list->quote;
	new_node->expansion_type = NO_EXPANSION;
	new_node->tok = minishell->t_list->tok; // ← ¡COPIA el tokenizer!
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

char	*extract_word(t_minishell *shell)
{
	int	start;

	start = shell->t_list->tok->pos;
	while (is_word_char(shell->t_list->tok->input[shell->t_list->tok->pos]))
		shell->t_list->tok->pos++;
	if (shell->t_list->tok->pos == start)
		return (NULL);
	shell->t_list->type = T_WORD;
	return (ft_substr(shell->t_list->tok->input, start, shell->t_list->tok->pos
			- start));
}

char	*extract_token(t_minishell *m)
{
	char	*val;

	// Saltar espacios
	while (m->t_list->tok->input[m->t_list->tok->pos] == ' '
		|| m->t_list->tok->input[m->t_list->tok->pos] == '\t')
		m->t_list->tok->pos++;
	// Fin de input
	if (m->t_list->tok->input[m->t_list->tok->pos] == '\0')
		return (NULL);
	// Intentar extraer metacharacter (|, >, <, etc.)
	val = extract_metachar(m);
	if (val)
		return (val);
	// Si no, extraer token complejo o palabra
	return (extract_complex_token(m));
}
