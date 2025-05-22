#include "../Mini.h"

void	mark_as_exported(char *name, t_env **env_list)
{
	t_env	*var;

	var = find_env(*env_list, name);
	if (var)
		var->exported = 1;
	else
		add_env_node(env_list, name, NULL, 1);
}

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
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **argv, t_env **env_list)
{
	int		i;
	char	*equal;
	char	*name;

	i = 1;
	if (!argv[1])
	{
		print_sorted_env(*env_list);
		return ;
	}
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=');
		if (equal)
			name = ft_substr(argv[i], 0, equal - argv[i]);
		else
			name = ft_strdup(argv[i]);

		if (!is_valid_identifier(name))
			printf("export: `%s`: not a valid identifier\n", argv[i]);
		else if (equal)
			add_or_update_env(argv[i], env_list);  // caso export VAR=value
		else
			mark_as_exported(name, env_list);     // caso export VAR

		free(name);
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
