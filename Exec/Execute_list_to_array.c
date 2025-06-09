/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_list_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:38:28 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 14:38:29 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

int	env_list_size(t_env	*env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->exported && env->name)
			count++;
		env = env->next;
	}
	return (count);
}

char	*env_entry(t_env *node)
{
	char	*entry;
	char	*result;

	entry = ft_strjoin(node->name, "=");
	if (!entry)
		return (NULL);
	if (node->value)
		result = ft_strjoin(entry, node->value);
	else
		result = ft_strdup(entry);
	free(entry);
	return (result);
}

char	**env_to_array(t_env *env_list)
{
	char	**env_array;
	int		i;
	int		size;

	size = env_list_size(env_list);
	i = 0;
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	while (env_list)
	{
		if (env_list->exported && env_list->name)
		{
			env_array[i] = env_entry(env_list);
			if (!env_array)
				return (ft_freedoom(env_array), NULL);
			i++;
		}
		env_list = env_list->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
