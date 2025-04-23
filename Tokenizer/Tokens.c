/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:28:37 by astefane          #+#    #+#             */
/*   Updated: 2025/04/23 16:45:08 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

static t_token_type	get_operator_type(char *input, int i, int *len)
{
	if (!input || input[i] == '\0')
		return (T_WORD);
	if (input[i] == '|')
	{
		*len = 1;
		return (T_PIPE);
	}
	if (input[i] == '<' && input[i + 1] == '<')
	{
		*len = 2;
		return (T_HEREDOC);
	}
	if (input[i] == '>' && input[i + 1] == '>')
	{
		*len = 2;
		return (T_RED_APPEND);
	}
	if (input[i] == '<')
	{
		*len = 1;
		return (T_RED_IN);
	}
	if (input[i] == '>')
	{
		*len = 1;
		return (T_RED_OUT);
	}
	return (T_WORD);
}

t_token	*init_token_list(char *input)
{
	t_token	*list;

	list = malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->input = ft_strdup(input);
	list->tokens = NULL;
	list->num_tokens = 0;
	return (list);
}

void	count_args(t_token *list)
{
	int	i;
	int	op_len;

	list->num_tokens = 0;
	i = 0;
	if (!list || !list->input)
		return ;
	while (list->input[i])
	{
		while (list->input[i] == ' ' || list->input[i] == '\t')
			i++;
		if (!list->input[i])
			break ;
		list->num_tokens++;
		op_len = 0;
		if (get_operator_type(list->input, i, &op_len) != T_WORD)
			i += op_len;
		else
			while (list->input[i] && list->input[i] != ' '
				&& list->input[i] != '\t' && get_operator_type(list->input, i,
					&op_len) == T_WORD)
				i++;
	}
}

char	*extract_word(char *input, int *index, int start)
{
	int	len;
	int	op_len;

	if (!input || !index)
		return (NULL);
	len = 0;
	op_len = 0;
	while (input[*index] && input[*index] != ' ' && input[*index] != '\t'
		&& get_operator_type(input, *index, &op_len) == T_WORD)
	{
		len++;
		(*index)++;
	}
	if (!len)
		return (NULL);
	return (ft_substr(input, start, len));
}

char	*extract_token(char *input, int *index, t_token_type *type)
{
	int	start;
	int	op_len;

	if (!input || !index)
		return (NULL);
	start = *index;
	while (input[start] == ' ' || input[start] == '\t')
		start++;
	*index = start;
	*type = T_WORD;
	op_len = 0;
	*type = get_operator_type(input, start, &op_len);
	if (*type != T_WORD)
	{
		*index += op_len;
		return (ft_substr(input, start, op_len));
	}
	return (extract_word(input, index, start));
}
