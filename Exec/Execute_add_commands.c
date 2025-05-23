#include "../Mini.h"

void	add_command_to_list(t_command **head, t_command *new_cmd)
{
	t_command	*tmp;

	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

void	add_arg_to_command(t_command *cmd, char *arg)
{
	int		count;
	int		i;
	char	**new_argv;

	count = 0;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		exit_with_error("Error malloc argv\n", 1, 2);
	while (i < count)
	{
		new_argv[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	new_argv[count] = ft_strdup(arg);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

int	count_commands_list(t_minishell *mini)
{
	t_command	*cmd;
	int			count;

	count = 0;
	cmd = mini->command_list;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

char	**split_command(char *cmd)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_freedoom(cmd_split);
		return (NULL);
	}
	return (cmd_split);
}
