
#include "../Mini.h"

char	*get_filename(int index)
{
	char	*number;
	char	*filename;
	char	*temp;

	number = ft_itoa(index);
	if (!number)
		return (NULL);
	temp = ft_strjoin("minishell_", number);
	free(number);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(temp, ".temp");
	free(temp);
	return (filename);
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

int	get_heredoc_index(t_token *token, t_token *target)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == T_HEREDOC)
		{
			if (token == target)
				return (i);
			i++;
		}
		token = token->next;
	}
	return (0);
}

void	apply_heredoc(t_command *cmd)
{
	int	fd_in;

	fd_in = open(cmd->heredoc_file, O_RDONLY);
	if (fd_in == -1)
		exit_with_error("Error opening heredoc\n", 1, 2);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_with_error("Error dup2 heredoc\n", 1, 2);
	close(fd_in);
}

void	redir_heredoc(t_command *cmd)
{
	int	fd_in;

	fd_in = open(cmd->heredoc_file, O_RDONLY);
	if (fd_in == -1)
		exit_with_error("Error opening heredoc\n", 1, 2);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_with_error("Error doing dup2 heredoc\n", 1, 2);
	close(fd_in);
}
