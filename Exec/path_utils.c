/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:52:06 by alejaro2          #+#    #+#             */
/*   Updated: 2025/05/05 21:02:15 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

char	*get_env_value(char **envp, const char *key)
{
	size_t	len;
	char	**ptr;

	len = ft_strlen(key);
	ptr = envp;
	while (*ptr)
	{
		if (ft_strncmp(*ptr, key, len) == 0 && (*ptr)[len] == '=')
			return (*ptr + len + 1);
		ptr++;
	}
	return (NULL);
}

static void	free_dirs(char **dirs)
{
	int	i;

	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
}
char *search_in_dirs(char **dirs, char *cmd)
{
	char *full;
	char *candidate;
	int i;
	
	i = 0;
	while (dirs[i])
	{
		full = ft_strjoin(dirs[i], "/");
		candidate = ft_strjoin(full, cmd);
		free(full);
		if(access(candidate, X_OK) == 0)
			return(candidate);
		free(candidate);
		i++;
	}
	return(NULL);
}

char	*find_in_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**dirs;
	char	*res;

	path_env = get_env_value(envp, "PATH");
	if (path_env == NULL)
		return (NULL);
	dirs = ft_split(path_env, ':');
	res = search_in_dirs(dirs, cmd);
	free_dirs(dirs);
	return(res);
}
