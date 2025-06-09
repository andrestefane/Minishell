

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
	new_node->type = minishell->tokenizer->prev_type;  // ✅ usa tokenizer real
	new_node->quote = Q_NONE; // o usa minishell->tokenizer->quote si lo implementás
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

	// ✅ Usar tokenizer directamente
	start = m->tokenizer->pos;

	// ✅ Avanzar mientras sea carácter válido
	while (is_word_char(m->tokenizer->input[m->tokenizer->pos]))
		m->tokenizer->pos++;

	if (m->tokenizer->pos == start)
		return (NULL);  // nada extraído

	// ✅ Extraer la subcadena
	word = ft_substr(m->tokenizer->input, start, m->tokenizer->pos - start);

	return (word);
}

char	*extract_token(t_minishell *m)
{
	char	*val;

	// Saltar espacios
	while (m->tokenizer->input[m->tokenizer->pos] == ' ' ||
		   m->tokenizer->input[m->tokenizer->pos] == '\t')
		m->tokenizer->pos++;

	// Fin de input
	if (m->tokenizer->input[m->tokenizer->pos] == '\0')
		return (NULL);

	// Intentar extraer metacharacter (|, >, <, etc.)
	val = extract_metachar(m);
	if (val)
		return (val);

	// Si no, extraer token complejo o palabra
	return (extract_complex_token(m));
}
