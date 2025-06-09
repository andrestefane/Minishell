/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_more_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:30:33 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 12:37:07 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	add_env_node(t_minishell *mini, char *name, char *value, int exported)
{
	t_env	*tmp;
	t_env	*new;

	tmp = mini->env_list;
	if (update_existing_node(tmp, name, value, exported))
		return ;
	new = create_new_node(name, value, exported);
	if (!new)
		return ;
	append_node_to_list(mini, new);
}

int	update_existing_node(t_env *tmp, char *name, char *value, int exported)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			update_node_value(tmp, value, exported);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	update_node_value(t_env *tmp, char *value, int exported)
{
	if (tmp->value)
		free(tmp->value);
	if (value)
		tmp->value = ft_strdup(value);
	else
		tmp->value = NULL;
	tmp->exported = exported;
}

t_env	*create_new_node(char *name, char *value, int exported)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
	}
	else
	{
		new->value = NULL;
	}
	new->exported = exported;
	new->signal = 0;
	new->next = NULL;
	return (new);
}

void	append_node_to_list(t_minishell *mini, t_env *new)
{
	t_env	*tmp;

	if (!mini->env_list)
	{
		mini->env_list = new;
	}
	else
	{
		tmp = mini->env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
