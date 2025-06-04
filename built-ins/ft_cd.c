#include "../Mini.h"

char	*get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value ? ft_strdup(env->value) : NULL);
		env = env->next;
	}
	return (NULL);
}

void	ft_cd(char **argv, t_env **env_list)
{
	char	*path;

	if (argv[1] && argv[2])
	{
		ft_putstr("cd: too many arguments\n", 2);
		g_status = 1;
		return ;
	}
	if (!argv[1])
	{
		path = get_env_value("HOME", *env_list);
		if (!path)
		{
			ft_putstr("cd: HOME not set\n", 2);
			g_status = 1;
			return ;
		}
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		g_status = 1;
	}
	else
		g_status = 0;
	if (!argv[1])
		free(path);
}
