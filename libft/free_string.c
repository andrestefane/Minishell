/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:16:35 by astefane          #+#    #+#             */
/*   Updated: 2025/05/05 20:46:10 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_and_error(char *str, char *message, int exit_code, int std)
{
	free(str);
	ft_putstr(message, std);
	exit(exit_code);
}
