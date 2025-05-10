/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:50:06 by astefane          #+#    #+#             */
/*   Updated: 2025/05/06 15:25:01 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	redir_outfile(t_command *cmd)
{
	int	fd_out;

	if (cmd->append == 1)
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_with_error("Error opening outfile\n", 1, 2);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_with_error("Error doing dup2 outfile\n", 1, 2);
	close(fd_out);
}

void	apply_outfile(t_command *cmd)
{
	int	fd_out;

	if (cmd->append == 1)
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_with_error("Error opening outfile\n", 1, 2);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_with_error("Error dup2 outfile\n", 1, 2);
	close(fd_out);
}
