/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:00:33 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 12:00:36 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

char	*get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			if (env->value)
				return (ft_strdup(env->value));
			else
				return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_cd(t_minishell *mini)
{
	char	*path;

	if (mini->command_list->argv[1] && mini->command_list->argv[2])
	{
		ft_putstr("cd: too many arguments\n", 2);
		g_status = 1;
		return ;
	}
	if (!mini->command_list->argv[1])
	{
		path = get_env_value("HOME", mini->env_list);
		if (!path)
		{
			(ft_putstr("cd: HOME not set\n", 2), g_status = 1);
			return ;
		}
	}
	else
		path = mini->command_list->argv[1];
	if (chdir(path) == -1)
		(perror("cd"), g_status = 1);
	else
		g_status = 0;
	if (!mini->command_list->argv[1])
		free(path);
}
