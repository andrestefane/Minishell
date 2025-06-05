#include "../Mini.h"

static int	is_token_char(char c)
{
	return (c && c != ' ' && c != '\t' && !ft_strchr("|<>", c));
}

int	fill_tokens(t_minishell *minishell, char *input)
{
	char	*val;

	// Limpiar tokens anteriores
	if (minishell->t_list)
	{
		free_t_list(minishell->t_list);
		minishell->t_list = NULL;
	}
	// Inicializar primer token + tokenizer
	minishell->t_list = malloc(sizeof(t_token));
	if (!minishell->t_list)
		return (0);
	minishell->t_list->tok = malloc(sizeof(t_tokenizer));
	if (!minishell->t_list->tok)
	{
		free(minishell->t_list);
		minishell->t_list = NULL;
		return (0);
	}
	minishell->t_list->tok->input = input;
	minishell->t_list->tok->pos = 0;
	minishell->t_list->tok->prev_type = T_WORD;
	minishell->t_list->tok->err = 0;
	minishell->t_list->next = NULL;
	while (!minishell->t_list->tok->err)
	{
		val = extract_token(minishell);
		if (minishell->t_list->tok->err)
			break ;
		if (!val )
			return(1);
		create_token_and_detect_expansion(minishell, val);
		free(val);
		minishell->t_list->tok->prev_type = minishell->t_list->type;
	}
	return (0);
}

char	*extract_quoted_token(t_minishell *m)
{
	int		j;
	char	*val;
	char	quote_char;

	quote_char = m->t_list->tok->input[m->t_list->tok->pos];
	j = m->t_list->tok->pos + 1;
	while (m->t_list->tok->input[j] && m->t_list->tok->input[j] != quote_char)
		j++;
	if (m->t_list->tok->input[j] == '\0')
	{
		m->t_list->tok->err = 1;
		return (NULL);
	}
	val = ft_substr(m->t_list->tok->input, m->t_list->tok->pos + 1, j
			- m->t_list->tok->pos - 1);
	m->t_list->type = T_WORD;
	m->t_list->quote = (quote_char == '\'') ? Q_SINGLE : Q_DOUBLE;
	m->t_list->tok->pos = j + 1;
	return (val);
}

static void	print_unclosed_error(char d)
{
	if (d == '\'')
		write(2, "minishell: syntax error: unclosed '\n", 37);
	else
		write(2, "minishell: syntax error: unclosed \"\n", 37);
}

static int	handle_quote(t_tokenizer *tok, char *res, size_t *i, char d)
{
	while (tok->input[tok->pos] && tok->input[tok->pos] != d)
		res[(*i)++] = tok->input[tok->pos++];
	if (tok->input[tok->pos] != d)
		return (0);
	tok->pos++;
	return (1);
}

static int	fill_complex_res(t_tokenizer *tok, char *res, size_t *idx)
{
	char	d;

	while (tok->input[tok->pos] && is_token_char(tok->input[tok->pos]))
	{
		d = tok->input[tok->pos++];
		if (d == '\'' || d == '"')
		{
			if (!handle_quote(tok, res, idx, d))
			{
				print_unclosed_error(d);
				return (0);
			}
		}
		else
			res[(*idx)++] = d;
	}
	res[*idx] = '\0';
	return (1);
}

char	*extract_complex_token(t_minishell *m)
{
	char	*res;
	size_t	idx;

	if (m->t_list->tok->input[m->t_list->tok->pos] == '\''
		|| m->t_list->tok->input[m->t_list->tok->pos] == '"')
		return (extract_quoted_token(m));
	res = malloc(ft_strlen(m->t_list->tok->input) + 1);
	if (!res)
	{
		m->t_list->tok->err = 1;
		return (NULL);
	}
	m->t_list->quote = Q_NONE;
	idx = 0;
	if (!fill_complex_res(m->t_list->tok, res, &idx))
	{
		m->t_list->tok->err = 1;
		free(res);
		return (NULL);
	}
	m->t_list->type = T_WORD;
	return (res);
}
