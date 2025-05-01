/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:28:37 by astefane          #+#    #+#             */
/*   Updated: 2025/05/01 16:51:22 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new_node;
	t_token	*current;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->value = ft_strdup(value);
	new_node->type = type;
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

char *extract_word(char *input, int *index, int start)
{
    int len;

    if (!input || !index)
        return (NULL);
    len = 0;
    while (input[*index] && input[*index] != ' ' && input[*index] != '\t'
           && input[*index] != '|' && input[*index] != '<' && input[*index] != '>')
    {
        len++;
        (*index)++;
    }
    if (!len)
        return (NULL);
    return (ft_substr(input, start, len));
}

char *extract_token(char *input, int *index, t_token_type *type, t_token_type prev_type)
{
    if (!input || !index || !type)
        return (NULL);
    while (input[*index] && (input[*index] == ' ' || input[*index] == '\t'))
        (*index)++;
    if (!input[*index])
        return (NULL);
    return (extract_token_aux(input, index, type, prev_type));
}


