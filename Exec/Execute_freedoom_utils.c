/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_freedoom_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:31:15 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 14:31:16 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	free_and_error(char *str, char *message, int exit_code, int std)
{
	free(str);
	ft_putstr(message, std);
	exit(exit_code);
}

void	free_stuct(t_pipex *data)
{
	if (data->pid)
		free(data->pid);
	free(data);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->filename);
		free(tmp);
	}
}
