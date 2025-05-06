/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:05:43 by astefane          #+#    #+#             */

/*   Updated: 2025/05/01 18:38:51 by alejaro2         ###   ########.fr       */

/*   Updated: 2025/04/30 20:21:22 by astefane         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	check_type(t_token *token, char **envir)
{
	int		has_input;
	int		has_pipe;
	int		has_output;
	t_token	*tmp;

	has_input = 0;
	has_pipe = 0;
	has_output = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == T_RED_IN || tmp->type == T_HEREDOC)
			has_input = 1;
		else if (tmp->type == T_PIPE)
			has_pipe = 1;
		else if (tmp->type == T_RED_OUT || tmp->type == T_RED_APPEND)
			has_output = 1;
		tmp = tmp->next;
	}
	pipex(token, envir);
}

void	execute_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	char    *path;

	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		if (ft_strchr(cmd->argv[0], '/') != NULL)
			path = cmd->argv[0];
		else
			path = find_in_path(cmd->argv[0], envp);
		if (path == NULL)
		{
			ft_putstr(cmd->argv[0], STDERR_FILENO);
			ft_putstr(": command not found\n", STDERR_FILENO);
			exit(127);
		}
		execve(path, cmd->argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}
