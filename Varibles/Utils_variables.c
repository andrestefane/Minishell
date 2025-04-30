
#include "../Mini.h"

int	is_simple_quotes(char *str)
{
	if (!str)
		return (0);
	return (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'');
}

void	expand_tilde(t_single_token *token, char **env)
{
	char	*home;
	char	*expanded;
	char	*path;

	path = "/bin/echo";

	if (!token || !token->value)
		return ;
	// SOLO expandimos si es "~" o "~/" al principio
	if (token->value[1] != '\0' && token->value[1] != '/')
		return ;
	home = getenv("HOME");
	execl(path, &token->value[0], env);
	if (!home)
		return ;
	if (token->value[1] == '\0')
		expanded = ft_strdup(home);
	else
		expanded = ft_strjoin(home, token->value + 1);
	if (!expanded)
		return ;
	free(token->value);
	token->value = expanded;
}
