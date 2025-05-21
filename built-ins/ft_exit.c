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

int	ft_exit(char **argv)
{
	int	code;

	ft_putstr("exit\n", 2);
	if (!argv[1])
		exit(g_status);
	if (argv[2])
	{
		ft_putstr("exit; too many arguments\n", 2);
		return (1);
	}
	if (!is_numeric(argv[1]))
	{
		ft_putstr("exit: ", 2);
		ft_putstr(argv[1], 2);
		ft_putstr(": numeric argument required\n", 2);
		exit (255);
	}
	code = ft_atoi(argv[1]);
	exit(code % 256);
}
