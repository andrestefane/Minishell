/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:24:24 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 14:24:25 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

void	ft_pwd(char **argv, char **env)
{
	char	*cwd;

	(void)argv;
	(void)env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr("Error pwd\n", 2);
		return ;
	}
	ft_putstr(cwd, 1);
	ft_putstr("\n", 1);
	free(cwd);
}
