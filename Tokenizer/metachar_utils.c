#include "../Mini.h"

static int	extract_double_metachar(t_minishell *m)
{
	char	c;

	c = m->t_list->tok->input[m->t_list->tok->pos];
	if ((c == '>' && m->t_list->tok->input[m->t_list->tok->pos + 1] == '>')
		|| (c == '<' && m->t_list->tok->input[m->t_list->tok->pos + 1] == '<'))
	{
		if (c == '>')
			m->t_list->type = T_RED_APPEND;
		else
			m->t_list->type = T_HEREDOC;
		mini->t_list->tok->pos += 2;
		return (1);
	}
	return (0);
}

static int	extract_single_metachar(t_tokenizer *tok, t_token_type *type)
{
	char	c;

	c = tok->input[tok->pos];
	if (c == '|')
		*type = T_PIPE;
	else if (c == '>')
		*type = T_RED_OUT;
	else if (c == '<')
		*type = T_RED_IN;
	else
		return (0);
	tok->pos++;
	return (1);
}

int	extract_metachar(t_minishell *mini)
{
	mini->t_list->quote = Q_NONE;
	if (extract_double_metachar(mini))
		return (1);
	if (extract_single_metachar(tok, type))
		return (1);
	return (0);
}
