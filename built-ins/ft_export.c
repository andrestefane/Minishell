#include "../Mini.h"

t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*equal;
	char	*name;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			name = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			add_env_node(&env_list, name, value, 1);
			free(name);
			free(value);
		}
		i++;
	}
	return (env_list);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i] || str[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **argv, t_env **env_list)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		print_sorted_env(*env_list);
		return ;
	}
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
			printf("export: `%s`: not a valid identifier\n", argv[i]);
		else
			add_or_update_env(argv[i], env_list);
		i++;
	}
}

void	sort_env_array(t_env **arr, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(arr[i]->name, arr[j]->name) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

