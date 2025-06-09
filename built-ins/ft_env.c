/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:17:05 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 12:17:09 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	ft_env(char **argv, char **env)
{
	int	i;

	(void)argv;
	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}
