/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:37:01 by astefane          #+#    #+#             */
/*   Updated: 2025/04/17 19:10:45 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mini.h"

int	main(int argc, char **env)
{
	t_token	*list;

	(void)env;
	list = malloc(sizeof(t_token));
	if (!list)
		exit_with_error("Error in first malloc\n", 1);
	if (argc != 1)
		exit_with_error("Alot of arguments\n", 1);
	*list = (t_token){0};
	ft_exec(list); //Bucle infinito aqui
	free(list);
	return (0);
}
