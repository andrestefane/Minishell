#include "../Mini.h"

void	remove_env_var(const char *name, t_env **env_list)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(char **argv, t_env **env_list)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		remove_env_var(argv[i], env_list);  // sin validación
		i++;
	}
}
