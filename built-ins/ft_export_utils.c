/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:25:49 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 14:15:34 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	mark_as_exported(char *name, t_minishell *mini)
{
	t_env	*var;

	var = find_env(mini->env_list, name);
	if (var)
		var->exported = 1;
	else
		add_env_node(mini, name, NULL, 1);
}

int	count_exported(t_minishell *mini)
{
	int		count;
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

