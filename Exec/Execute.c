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

void	check_type(t_token *token, char **envir, t_command *cmd)
{
	int			has_input;
	int			has_pipe;
	int			has_output;
	t_token		*tmp;

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
	if ((has_input && has_pipe && has_output) || (has_input && has_output))
		pipex(token, envir);
	else
		execute_command(cmd, envir);
}

void execute_command(t_command *cmd, char **envp)
{
    pid_t pid = fork();
    if (pid < 0)
        perror("fork");
    else if (pid == 0)
    {
        execve(cmd->argv[0], cmd->argv, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
        waitpid(pid, NULL, 0);
}
