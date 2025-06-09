/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:00:26 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 12:00:29 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	ft_echo_arg(char **argv)
{
	int	new_line;
	int	i;
	int	j;

	i = 1;
	new_line = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr(argv[i], 1);
		if (argv[i + 1])
			ft_putstr(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr("\n", 1);
}
