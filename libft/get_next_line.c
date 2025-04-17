/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:25:54 by astefane          #+#    #+#             */
/*   Updated: 2025/04/17 18:30:46 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_gnl(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_cleanline_gnl(char *str)
{
	char			*newstring;
	char			*character;
	unsigned int	len;

	character = ft_strchr_gnl(str, '\n');
	if (!character)
	{
		newstring = NULL;
		return (ft_free_gnl(&str));
	}
	else
		len = (unsigned int)(character - str) + 1;
	if (!str[len])
		return (ft_free_gnl(&str));
	newstring = ft_substr_gnl(str, len, ft_strlen_gnl(str) - len);
	if (!newstring)
		return (NULL);
	ft_free_gnl(&str);
	return (newstring);
}

char	*ft_get_line_gnl(char *str)
{
	char			*line;
	char			*character;
	size_t			len;

	if (!str)
		return (NULL);
	character = ft_strchr_gnl(str, '\n');
	len = (size_t)(character - str) + 1;
	line = ft_substr_gnl(str, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_reading_gnl(int fd, char *str)
{
	char		*buffer;
	ssize_t		bytes_read;

	if (BUFFER_SIZE < 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_gnl(&str));
	bytes_read = 1;
	buffer[0] = '\0';
	while (!ft_strchr_gnl(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			str = ft_strjoin_gnl(str, buffer);
		}
	}
	free(buffer);
	if (bytes_read == -1)
		return (ft_free_gnl(&str));
	return (str);
}

char	*get_next_line(int fd, int mode)
{
	static char	*str;
	char		*line;

	if (mode == 1)
	{
		ft_free_gnl(&str);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((str && !ft_strchr_gnl(str, '\n')) || !str)
		str = ft_reading_gnl(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line_gnl(str);
	if (!line)
		return (ft_free_gnl(&str));
	str = ft_cleanline_gnl(str);
	return (line);
}

/* char	*get_next_line(int fd, int mode)
{
	static char	*str[1024];
	char		*line;

	if (mode == 1)
	{
		ft_free(&str);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((str[fd] && !ft_strchr(str[fd], '\n')) || !str[fd])
		str[fd] = ft_reading(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_get_line(str[fd]);
	if (!line)
		return (ft_free(&str[fd]));
	str[fd] = ft_cleanline(str[fd]);
	return (line);
} */

/* int	main(int argc, char *argv[])
{
	char	*line;
	int		fd;

	if (argc != 2)
	{
		printf("Insert arguments");
	}
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
} */