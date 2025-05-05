/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:56:24 by astefane          #+#    #+#             */
/*   Updated: 2025/05/03 20:31:22 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_filename(int index)
{
	char	*number;
	char	*filename;
	char	*temp;

	number = ft_itoa(index);
	if (!number)
		return (NULL);
	temp = ft_strjoin("temp/here_doc_", number);
	free(number);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(temp, ".temp");
	free(temp);
	return (filename);
}

void	handle_all_heredocs(t_token *token, t_pipex *data)
{
	t_token	*tmp;
	char	*filename;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC && tmp->next && tmp->next->value)
		{
			filename = get_filename(count);
			if (!filename)
				exit_with_error("filename of heredoc failed\n", 1, 2);
			if (here_doc(tmp, filename) == -1)
				free_and_error(filename, "Error Reading heredoc\n", 1, 2);
			free(filename);
			count++;
		}
		tmp = tmp->next;
	}
	data->count_heredoc = count;
}

int	is_limiter(char *line, char *limiter)
{
	if (!limiter)
		return (0);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& line[ft_strlen(limiter)] == '\n')
		return (1);
	return (0);
}

int	here_doc(t_token *token, const char *filename)
{
	int		fd;
	t_token	*next;
	char	*line;

	next = token->next;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		unlink(filename);
		exit_with_error(ERRO_DOC, 1, 2);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0, 0);
		if (!line || is_limiter(line, next->value))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}

void	delete_heredoc_files(int n)
{
	int		i;
	char	*filename;

	i = 0;
	while (i < n)
	{
		filename = get_filename(i);
		if (filename)
		{
			unlink(filename);
			free(filename);
		}
		i++;
	}
}
