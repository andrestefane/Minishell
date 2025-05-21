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

int	ft_exit(t_command *cmd)
{
	int	code;

	ft_putstr("exit\n", 2);
	if (!cmd->argv[1])
		exit(g_status);
	if (cmd->argv[2])
	{
		ft_putstr("exit; too many arguments\n", 2);
		return (1);
	}
	if (!is_numeric(cmd->argv[1]))
	{
		ft_putstr("exit: ", 2);
		ft_putstr(cmd->argv[1], 2);
		ft_putstr(": numeric argument required\n", 2);
		exit (255);
	}
	code = ft_atoi(cmd->argv[1]);
	exit(code % 256);
}
