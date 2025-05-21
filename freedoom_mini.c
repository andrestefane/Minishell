#include "Mini.h"

void	free_env_list(t_env	*env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env)
	}
}
