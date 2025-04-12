/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:46:37 by astefane          #+#    #+#             */
/*   Updated: 2024/04/03 13:43:21 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;

	csrc = (char *) src;
	cdest = (char *)dest;
	if (dest == 0 && src == 0)
		return (0);
	if (csrc < cdest && csrc + n > cdest)
	{
		cdest += n;
		csrc += n;
		while (n--)
			*--cdest = *--csrc;
	}
	else
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	return (dest);
}
