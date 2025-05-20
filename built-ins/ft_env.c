
#include "../Mini.h"


void	ft_env(char **argv, char **env)
{
	int	i;

	(void)argv;
	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}
