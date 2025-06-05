#include "../Mini.h"

static int	extract_double_metachar(t_minishell *m)
{
	char	c;

	c = m->tokenizer->input[m->tokenizer->pos];
	if ((c == '>'
			&& m->tokenizer->input[m->tokenizer->pos + 1] == '>')
		|| (c == '<' && m->tokenizer->input[m->tokenizer->pos + 1] == '<'))
	{
		if (c == '>')
			m->tokenizer->prev_type = T_RED_APPEND;
		else
			m->tokenizer->prev_type = T_HEREDOC;
		m->tokenizer->pos += 2;
		return (1);
	}
	return (0);
}

static int	extract_single_metachar(t_minishell *m)
{
	char	c;

	c = m->tokenizer->input[m->tokenizer->pos];
	if (c == '|')
		m->tokenizer->prev_type = T_PIPE;
	else if (c == '>')
		m->tokenizer->prev_type = T_RED_OUT;
	else if (c == '<')
		m->tokenizer->prev_type = T_RED_IN;
	else
		return (0);
	m->tokenizer->pos++;
	return (1);
}

char	*extract_metachar(t_minishell *m)
{
	char	*symbol = NULL;

	// No hay comillas en metachars
	m->tokenizer->err = 0;

	if (extract_double_metachar(m))
		symbol = ft_substr(m->tokenizer->input, m->tokenizer->pos - 2, 2);
	else if (extract_single_metachar(m))
		symbol = ft_substr(m->tokenizer->input, m->tokenizer->pos - 1, 1);

	return (symbol);
}
