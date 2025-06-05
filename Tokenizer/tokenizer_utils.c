#include "../Mini.h"

static int	is_token_char(char c)
{
	return (c && c != ' ' && c != '\t' && !ft_strchr("|<>", c));
}

int	fill_tokens(t_minishell *minishell, char *input)
{
	char	*val;
	int		success = 1; // bandera para el retorno

	// Limpiar tokens previos
	if (minishell->t_list)
	{
		free_t_list(minishell->t_list);
		minishell->t_list = NULL;
	}
	// Liberar tokenizer anterior
	if (minishell->tokenizer)
		free(minishell->tokenizer);
	// Inicializar nuevo tokenizer
	minishell->tokenizer = malloc(sizeof(t_tokenizer));
	if (!minishell->tokenizer)
		return (0); // error
	minishell->tokenizer->input = input;
	minishell->tokenizer->pos = 0;
	minishell->tokenizer->prev_type = T_WORD;
	minishell->tokenizer->quote = Q_NONE;
	minishell->tokenizer->err = 0;

	while (!minishell->tokenizer->err)
	{
		val = extract_token(minishell);

		if (minishell->tokenizer->err)
			break;

		if (!val) // fin de input
			break;

		if (!create_token_and_detect_expansion(minishell, val))
		{
			success = 0; // error al crear token
			free(val);
			break;
		}
		free(val);
	}

	free(minishell->tokenizer);
	minishell->tokenizer = NULL;

	if (minishell->tokenizer && minishell->tokenizer->err)
		success = 0;

	if (!success)
	{
		free_t_list(minishell->t_list);
		minishell->t_list = NULL;
	}

	return (success);
}


char	*extract_quoted_token(t_minishell *m)
{
	int		j;
	char	*val;
	char	quote_char;

	// Leer comilla inicial
	quote_char = m->tokenizer->input[m->tokenizer->pos];

	// Buscar final de la comilla
	j = m->tokenizer->pos + 1;
	while (m->tokenizer->input[j] && m->tokenizer->input[j] != quote_char)
		j++;

	// Si no se cerró la comilla
	if (m->tokenizer->input[j] == '\0')
	{
		m->tokenizer->err = 1;
		return (NULL);
	}

	// Extraer el contenido entre comillas
	val = ft_substr(m->tokenizer->input,
					m->tokenizer->pos + 1,
					j - m->tokenizer->pos - 1);

	// Guardar tipo y quote en el tokenizer (temporal, para usar luego al crear token)
	m->tokenizer->prev_type = T_WORD;

	// ⚠ Si quieres guardar el tipo de quote, podrías agregar:
	// m->tokenizer->quote = (quote_char == '\'') ? Q_SINGLE : Q_DOUBLE;

	// Avanzar posición más allá de la comilla de cierre
	m->tokenizer->pos = j + 1;

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

	if (m->tokenizer->input[m->tokenizer->pos] == '\'' ||
		m->tokenizer->input[m->tokenizer->pos] == '"')
		return (extract_quoted_token(m));

	res = malloc(ft_strlen(m->tokenizer->input) + 1);
	if (!res)
	{
		m->tokenizer->err = 1;
		return (NULL);
	}

	m->tokenizer->quote = Q_NONE; // si querés resetear aquí

	idx = 0;

	if (!fill_complex_res(m->tokenizer, res, &idx))  // ✅ pasás el tokenizer
	{
		m->tokenizer->err = 1;
		free(res);
		return (NULL);
	}

	m->tokenizer->prev_type = T_WORD;

	return (res);
}
