/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:25:40 by astefane          #+#    #+#             */
/*   Updated: 2024/04/05 12:28:56 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t				i;
	unsigned int		x;
	unsigned int		st_len;

	st_len = ft_strlen(dst);
	x = ft_strlen(src);
	i = 0;
	if (size <= st_len)
		return (size + x);
	while (dst[i] && i < size - 1)
	{
		i++;
	}
	while (*src && i < size - 1)
	{
		dst[i++] = *src++;
	}
	dst[i] = '\0';
	return (st_len + x);
}
