#include "../Mini.h"

void	free_commands(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	free(cmd);
}
int check_syntax_pipes(t_token *tok)
{
    if (!tok)
        return (1);
    /* pipe al inicio */
    if (tok->type == T_PIPE)
    {
        ft_putstr("minishell: syntax error near unexpected token `|'\n", 2);
        return (0);
    }
    /* recorre hasta el último */
    while (tok->next)
    {
        if (tok->type == T_PIPE && tok->next->type == T_PIPE)
        {
            ft_putstr("minishell: syntax error near unexpected token `|'\n", 2);
            return (0);
        }
        tok = tok->next;
    }
    /* pipe al final */
    if (tok->type == T_PIPE)
    {
        ft_putstr("minishell: syntax error near unexpected token `|'\n", 2);
        return (0);
    }
    return (1);
}