#include "../Mini.h"

int	is_builtin(t_command *cmd)
{
	return (!ft_strcmp(cmd->argv[0], "echo")
		|| !ft_strcmp(cmd->argv[0], "cd")
		|| !ft_strcmp(cmd->argv[0], "pwd")
		|| !ft_strcmp(cmd->argv[0], "export")
		|| !ft_strcmp(cmd->argv[0], "unset")
		|| !ft_strcmp(cmd->argv[0], "env")
		|| !ft_strcmp(cmd->argv[0], "exit"));
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

void	execute_buitin(t_command *cmd, char ***env)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);
	(void)env;
/* 	else if (!ft_strcmp(cmd->argv[0], "cd"))
		ft_cd(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ft_pwd(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ft_export(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ft_unset(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ft_env(cmd->argv, env);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_exit(cmd->argv, env); */
}

void	execute_buitin_args(char **argv, char ***env)
{
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo_arg(argv);
	(void)env;
/* 	else if (!ft_strcmp(argv, "cd"))
		ft_cd(cmd->argv, env);
	else if (!ft_strcmp(argv, "pwd"))
		ft_pwd(cmd->argv, env);
	else if (!ft_strcmp(argv, "export"))
		ft_export(cmd->argv, env);
	else if (!ft_strcmp(argv, "unset"))
		ft_unset(cmd->argv, env);
	else if (!ft_strcmp(argv, "env"))
		ft_env(cmd->argv, env);
	else if (!ft_strcmp(argv, "exit"))
		ft_exit(cmd->argv, env); */
}
