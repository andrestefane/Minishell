/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:56:24 by astefane          #+#    #+#             */
/*   Updated: 2025/05/01 18:27:28 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	here_doc(t_token *token)
{
	int		fd;
	char	*line;
	t_token	*next;

	next = token->next;
	fd = open("here_doc.temp", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		unlink("here_doc.temp");
		exit_with_error(ERRO_DOC, 1, 2);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (next && ft_strncmp(line, next->value, ft_strlen(next->value)) == 0
			&& line[ft_strlen(next->value)] == '\n')
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	return (fd);
}

