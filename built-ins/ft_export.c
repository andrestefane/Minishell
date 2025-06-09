/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:14:30 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 15:26:52 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

t_env	*create_env_list(char **envp, t_minishell *mini)
{
	int		i;
	char	*equal;
	char	*name;
	char	*value;

	mini->env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			name = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			add_env_node(mini, name, value, 1);
			free(name);
			free(value);
		}
		i++;
	}
	return (mini->env_list);
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

void	ft_export(t_minishell *mini)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!mini->command_list->argv[1])
	{
		print_sorted_env(mini);
		return ;
	}
	while (mini->command_list->argv[i])
	{
		error = process_export_argument(mini->command_list->argv[i], mini);
		i++;
	}
	g_status = error;
}

int	process_export_argument(char *arg, t_minishell *mini)
{
	char	*equal;
	char	*name;
	int		error;

	error = 0;
	equal = ft_strchr(arg, '=');
	if (equal)
		name = ft_substr(arg, 0, equal - arg);
	else
		name = ft_strdup(arg);
	if (!is_valid_identifier(name))
	{
		ft_putstr("export: `", 2);
		ft_putstr(arg, 2);
		ft_putstr("': not a valid identifier\n", 2);
		error = 1;
	}
	else if (equal)
		add_or_update_env(arg, mini);
	else
		mark_as_exported(name, mini);
	free(name);
	return (error);
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
