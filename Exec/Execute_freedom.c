
#include "../Mini.h"

void	free_struct(t_pipex *data, char *message, int exit_code, int std)
{
	if (data)
	{
		if (data->pid)
		{
			free(data->pid);
			data->pid = NULL;
		}
		free(data);
	}
	ft_putstr(message, std);
	exit(exit_code);
}

void	exit_with_error(char *message, int exit_code, int std)
{
	ft_putstr(message, std);
	exit(exit_code);
}

void	free_command_list(t_command *cmd)
{
	t_command	*next;

	if (!cmd)
		return ;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->argv)
			ft_freedoom(cmd->argv);
		if (cmd->redirs)
			free_redirs(cmd->redirs);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->heredoc_file)
			free(cmd->heredoc_file);
		free(cmd);
		cmd = next;
	}
}

void	ft_freedoom(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	free_and_exit(char **args, char **paths, int exit_code)
{
	ft_freedoom(args);
	ft_freedoom(paths);
	exit(exit_code);
}
