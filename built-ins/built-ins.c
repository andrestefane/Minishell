#include "../Mini.h"

int	is_builtin(t_token *token)
{
	if (!token || !token->value)
		return (NO_BUITIN);
	if (!ft_strcmp(token->value, "echo")
		|| !ft_strcmp(token->value, "pwd")
		|| !ft_strcmp(token->value, "env"))
		return (BUILTIN_CHILD);
	else if (!ft_strcmp(token->value, "cd")
		|| !ft_strcmp(token->value, "exit")
		|| !ft_strcmp(token->value, "exit")
		|| !ft_strcmp(token->value, "export")
		|| !ft_strcmp(token->value, "unset"))
		return (BUILTIN_PARENT);
	return (NO_BUITIN);
}

int	is_builtin_str(char *str)
{
	return (!ft_strcmp(str, "echo")
		|| !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"));
}

void	execute_buitin(t_command *cmd, char ***env, t_env **env_list)
{
	(void)env;

	if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);
	else if(!ft_strcmp(cmd->argv[0], "export"))
		ft_export(cmd->argv, env_list);
	printf("DEBUG: estás usando TU built-in para %s en el padre\n", cmd->argv[0]);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_exit(cmd);

/* 	else if (!ft_strcmp(cmd->argv[0], "cd"))
		ft_cd(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ft_pwd(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ft_unset(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ft_env(cmd->argv, env);
	*/
}

void	execute_buitin_args(char **argv, char ***env)
{
	printf("DEBUG: estás usando TU built-in para %s\n", argv[0]);
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo_arg(argv);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(argv, *env);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(argv, *env);
	// else if (!ft_strcmp(argv[0], "export"))
	// 	ft_export(cmd->argv, env);
/* 	else if (!ft_strcmp(argv, "cd"))
		ft_cd(cmd->argv, env);
	else if (!ft_strcmp(argv, "unset"))
		ft_unset(cmd->argv, env);*/
}
