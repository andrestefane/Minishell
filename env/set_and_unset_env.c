#include "../Mini.h"

static char	*join_name_value(const char *name, const char *value)
{
	char	*temp;
	char	*result;
	size_t	name_len;
	size_t	value_len;

	if (!name || !value)
		return (NULL);
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	temp = malloc(name_len + 2);
	if (!temp)
		return (NULL);
	ft_strcpy (temp, name);
	temp[name_len] = '=';
	temp[name_len + 1] = '\0';
	result = malloc(name_len + value_len + 2);
	if (!result)
		return (free(temp), NULL);
	ft_strcpy(result, temp);
	ft_strcat(result, value);
	return (free(temp), result);
}

char	**append_env_variable(char **env, const char *name, const char *value)
{
	char	**new_env;
	char	*new_var;
	int		count;
	int		i;

	count = 0;
	while (env && env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = env[i];
		i++;
	}
	new_var = join_name_value(name, value);
	if (!new_var)
		return (free(new_env), NULL);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (free(env), new_env);
}

void	set_env(char ***env, const char *name, const char *value)
{
	int		i;
	int		len;
	char	*new_var;

	if (!env || !*env || !name || !value)
		return ;
	i = 0;
	len = ft_strlen(name);
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], name, len)
			&& (*env)[i][len] == '=')
		{
			free((*env)[i]);
			new_var = join_name_value(name, value);
			(*env)[i] = new_var;
			return ;
		}
		i++;
	}
	*env = append_env_variable(*env, name, value);
}
