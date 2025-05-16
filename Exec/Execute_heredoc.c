
#include "../Mini.h"

int	is_limiter(char *line, char *limiter)
{
	if (!limiter)
		return (0);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& line[ft_strlen(limiter)] == '\n')
		return (1);
	return (0);
}

int	here_doc(char *limiter, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (!limiter || !*limiter)
		exit_with_error(SYNTAX_ERROR, 1, 2);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0, 0);
		if (!line || ft_strcmp(line, limiter) == 0 || is_limiter(line, limiter))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}

char	*handle_heredoc_in_command(t_command *cmd, char *limiter, int index)
{
	char	*filename;

	filename = get_filename(index);
	if (!filename)
		exit_with_error("malloc filename failed\n", 1, 2);
	if (here_doc(limiter, filename) == -1)
		free_and_error(filename, "Error reading heredoc\n", 1, 2);
	cmd->is_heredoc = 1;
	cmd->heredoc_file = filename;
	return (filename);
}
