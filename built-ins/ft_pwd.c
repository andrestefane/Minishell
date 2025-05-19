#include "../Mini.h"

void	ft_pwd(char **argv, char **env)
{
	char	*cwd;

	(void)argv;
	(void)env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr("Error pwd\n", 2);
		return ;
	}
	ft_putstr(cwd, 1);
	ft_putstr("\n", 1);
	free(cwd);
}
