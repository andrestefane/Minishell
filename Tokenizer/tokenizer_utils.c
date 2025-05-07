#include "../Mini.h"

int fill_tokens(t_token **list, char *input)
{
    t_tokenizer    tok = { input, 0, T_WORD, 0 };
    t_token_type   type;
    t_token_quote  quote;
    char          *val;

    while (!tok.err)
    {
        val = extract_token(&tok, &type, &quote);
        if (tok.err)                   /* comilla sin cerrar */
            break;
        if (!val)                      /* fin de línea */
            return (1);
        add_token(list, val, type, quote);
        free(val);
        tok.prev_type = type;
    }
    /* si tok.err == 1, hubo error */
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
