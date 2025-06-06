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

void	add_env_node(t_minishell *mini, char *name, char *value, int exported)
{
	t_env	*tmp;
	t_env	*new;

	tmp = mini->env_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (tmp->value)
				free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			tmp->exported = exported;
			return;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return ;
	}
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->exported = exported;
	new->signal = 0;
	new->next = NULL;
	if (!mini->env_list)
		mini->env_list = new;
	else
	{
		tmp = mini->env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}


int	count_exported(t_minishell *mini)
{
	int	count;
	t_env	*tmp;

	tmp = mini->env_list;
	count = 0;
	while (mini->env_list)
	{
		if (mini->env_list->exported)
			count++;
		mini->env_list = mini->env_list->next;
	}
	mini->env_list = tmp;
	return (count);
}

void	print_sorted_env(t_minishell *mini)
{
	int		count;
	int		i;
	t_env	**arr;

	count = count_exported(mini);
	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return ;
	i = 0;
	while (mini->env_list)
	{
		if (mini->env_list->exported)
			arr[i++] = mini->env_list;
		ft_putstr("en export arr -1 name:", 2);
		mini->env_list = mini->env_list->next;
	}
	sort_env_array(arr, count);
	print_env_array(arr, count);
	free(arr);
}

void	add_or_update_env(char *arg, t_minishell *mini)
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
	var = find_env(mini->env_list, name);
	if (var)
	{
		free(var->value);
		var->value = value;
	}
	else
		add_env_node(mini, name, value, 1);
	free(name);
}
