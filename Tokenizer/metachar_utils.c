#include "../Mini.h"

static int	extract_double_metachar(t_minishell *m)
{
	char	*input = m->tokenizer->input + m->tokenizer->pos;

	// Contar cuántos '<' seguidos hay
	if (input[0] == '<') {
		int count = 0;
		while (input[count] == '<')
			count++;
		if (count > 2) {
			ft_putstr("minishell: syntax error near unexpected token `<<<'\n", STDERR_FILENO);
			m->tokenizer->err = 1;
			return (0);
		}
		if (count == 2) {
			m->tokenizer->prev_type = T_HEREDOC;
			m->tokenizer->pos += 2;
			return (1);
		}
	}
	// Lo mismo para '>' si quieres hacer validaciones similares, aunque no suele ser necesario

	if (input[0] == '>' && input[1] == '>') {
		m->tokenizer->prev_type = T_RED_APPEND;
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
