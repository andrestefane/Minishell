#include "../Mini.h"

void	ft_cd(char **argv)
{
	if (!argv[1])
	{
		ft_putstr("cd: missing argument\n", 2);
		return ;
	}
	if (chdir(argv[1]) == -1)
	{
		perror("cd");
	}
}
