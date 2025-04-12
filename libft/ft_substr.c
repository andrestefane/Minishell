/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:24:51 by astefane          #+#    #+#             */
/*   Updated: 2024/04/04 16:23:07 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		sub = ft_calloc(1, sizeof(char));
		if (!sub)
			return (NULL);
		return (sub);
	}
	new_len = ft_strlen(s + start);
	if (new_len > len)
		new_len = len;
	sub = (char *)malloc((new_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	sub[new_len] = '\0';
	while (new_len--)
		sub[new_len] = s[start + new_len];
	return (sub);
}
