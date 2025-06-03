#include "../Mini.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_command *cmd, t_minishell *minishell)
{
	int	code;

	ft_putstr("exit\n", 2);
	if (!cmd->argv[1])
	{
		free_minishell(minishell);
		free(minishell);
		exit(g_status);
	}
	if (cmd->argv[2])
	{
		ft_putstr(" too many arguments\n", 2);
		return (1);
	}
	if (!is_numeric(cmd->argv[1]))
	{
		ft_putstr("exit: ", 2);
		ft_putstr(cmd->argv[1], 2);
		ft_putstr(": numeric argument required\n", 2);
	/* 	free_minishell(minishell);
		free(minishell); */
		exit(255);
	}
	code = ft_atoi(cmd->argv[1]);
/* 	free_minishell(minishell);
	free(minishell); */
	exit(code % 256);
}
