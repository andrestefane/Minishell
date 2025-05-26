#include "../Mini.h"

static int	is_token_char(char c)
{
	return (c && c != ' ' && c != '\t' && !ft_strchr("|<>", c));
}

int	fill_tokens(t_minishell *minishell, char *input)
{
	t_tokenizer		tok;
	t_token_type	type;
	t_token_quote	quote;
	char			*val;

	tok.input = input;
	tok.pos = 0;
	tok.prev_type = T_WORD;
	tok.err = 0;
	while (!tok.err)
	{
		val = extract_token(&tok, &type, &quote);
		if (tok.err)
			break ;
		if (!val)
			return (1);
		t_token *tok_debug = create_token_and_detect_expansion(minishell, val, type, quote);
		printf("DEBUG Token generado: [%s] | Expansion Type: %d\n", tok_debug->value, tok_debug->expansion_type);
		free(val);
		tok.prev_type = type;
	}
	return (0);
}

char	*extract_quoted_token(t_tokenizer *tok, t_token_type *type,
		t_token_quote *quote)
{
	char	quote_char;
	int		j;
	char	*val;

	quote_char = tok->input[tok->pos];
	j = tok->pos + 1;
	while (tok->input[j] && tok->input[j] != quote_char)
		j++;
	if (tok->input[j] == '\0')
	{
		tok->err = 1;
		return (NULL);
	}
	val = ft_substr(tok->input, tok->pos + 1, j - tok->pos - 1);
	*type = T_WORD;
	if (quote_char == '\'')
		*quote = Q_SINGLE;
	else
		*quote = Q_DOUBLE;
	tok->pos = j + 1;
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

char	*extract_complex_token(t_tokenizer *tok, t_token_type *type,
		t_token_quote *quote)
{
	char	*res;
	size_t	idx;

	res = malloc(ft_strlen(tok->input) + 1);
	if (!res)
	{
		tok->err = 1;
		return (NULL);
	}
	*quote = Q_NONE;
	idx = 0;
	if (!fill_complex_res(tok, res, &idx))
	{
		tok->err = 1;
		free(res);
		return (NULL);
	}
	*type = T_WORD;
	return (res);
}
