#include "../Mini.h"

void	print_env_array(t_env **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("declare -x %s", arr[i]->name);
		if (arr[i]->value)
			printf("=\"%s\"", arr[i]->value);
		printf("\n");
		i++;
	}
}

t_env	*find_env(t_env *env_list, const char *name)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->name, name))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	add_env_node(t_env **env_list, char *name, char *value, int exported)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->exported = exported;
	new->next = NULL;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	count_exported(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->exported)
			count++;
		env = env->next;
	}
	return (count);
}
void	print_sorted_env(t_env *env)
{
	int		count;
	int		i;
	t_env	**arr;

	count = count_exported(env);
	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return ;
	i = 0;
	while (env)
	{
		if (env->exported)
			arr[i++] = env;
		env = env->next;
	}
	sort_env_array(arr, count);
	print_env_array(arr, count);
	free(arr);
}
void	add_or_update_env(char *arg, t_env **env_list)
{
	t_env	*var;
	char	*equal;
	char	*name;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return ;
	name = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	var = find_env(*env_list, name);
	if (var)
	{
		free(var->value);
		var->value = value;
	}
	else
		add_env_node(env_list, name, value, 1);
	free(name);
}
