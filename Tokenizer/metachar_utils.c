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
		m->t_list->tok->pos += 2;
		return (1);
	}
	return (0);
}

static int	extract_single_metachar(t_minishell *shell)
{
	char	c;

	c = shell->t_list->tok->input[shell->t_list->tok->pos];
	if (c == '|')
		shell->t_list->type = T_PIPE;
	else if (c == '>')
		shell->t_list->type = T_RED_OUT;
	else if (c == '<')
		shell->t_list->type = T_RED_IN;
	else
		return (0);
	shell->t_list->tok->pos++;
	return (1);
}


char	*extract_metachar(t_minishell *mini)
{
	char	*symbol = NULL;

	mini->t_list->quote = Q_NONE;

	if (extract_double_metachar(mini))
		symbol = ft_substr(mini->t_list->tok->input,
				mini->t_list->tok->pos - 2, 2);
	else if (extract_single_metachar(mini))
		symbol = ft_substr(mini->t_list->tok->input,
				mini->t_list->tok->pos - 1, 1);

	return (symbol);
}

