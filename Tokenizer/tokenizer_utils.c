#include "../Mini.h"

static char	*strip_quotes(const char *s)
{
	size_t	len;
	char	*dst;
	size_t	i = 0;
	size_t j = 0;

	len = strlen(s);
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '"' && s[i] != '\'')
			dst[j++] = s[i];
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

static char	*token_join(char *result, char *temp)
{
	char	*joined;

	if (!temp)
	{
		free(result);
		return (NULL);
	}
	joined = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (joined);
}

static int	is_token_char(char c)
{
	return (c && c != ' ' && c != '\t' && !ft_strchr("|<>", c));
}

int	fill_tokens(t_token **list, char *input)
{
	t_tokenizer		tok;
	t_token_type	type;
	t_token_quote	quote;
	char			*val;

	tok.input = input;      // usa el parámetro input
    tok.pos   = 0;
    tok.prev_type  = T_WORD;
    tok.err = 0;
	while (!tok.err)
	{
		val = extract_token(&tok, &type, &quote);
		if (tok.err)
			break ;
		if (!val)
			return (1);
		add_token(list, val, type, quote);
		// Añade esto temporalmente para diagnóstico inmediato:
		printf("DEBUG Token generado: [%s]\n", val);
		free(val);
		tok.prev_type = type;
	}
	free_tokens(*list);
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

char	*extract_complex_token(t_tokenizer *tok, t_token_type *type,
		t_token_quote *quote)
{
	char			*result;
	char			*temp;
	t_token_quote	current_quote;

	result = ft_strdup("");
	*quote = Q_NONE;
	while (is_token_char(tok->input[tok->pos]))
	{
		temp = get_next_token_part(tok, type, &current_quote);
		if (temp && is_empty_token(temp))
		{
			free(temp);
			continue ;
		}
		result = token_join(result, temp);
		if (!result)
			return (tok->err = 1, NULL);
		if (*quote == Q_NONE && current_quote != Q_NONE)
			*quote = current_quote;
		else if (*quote != current_quote)
			*quote = Q_NONE;
	}
	*type = T_WORD;
    {
        char *clean = strip_quotes(result);
        free(result);
        if (!clean)
        {
            tok->err = 1;
            return NULL;
        }
        return clean;
    }
}
