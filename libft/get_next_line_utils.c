/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:13:23 by astefane          #+#    #+#             */
/*   Updated: 2025/04/17 18:27:02 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*result;

	lens1 = ft_strlen_gnl(s1);
	lens2 = ft_strlen_gnl(s2);
	result = malloc(lens1 + lens2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy_gnl(result, s1, lens1);
	ft_memcpy_gnl(result + lens1, s2, lens2 + 1);
	free(s1);
	return (result);
}

void	*ft_memcpy_gnl(void *dst, const void *src, size_t n)
{
	void		*ret;
	char		*p_dst;
	const char	*p_src;

	if (!dst && !src)
		return (NULL);
	ret = dst;
	p_dst = (char *)dst;
	p_src = (const char *)src;
	while (n--)
		*p_dst++ = *p_src++;
	return (ret);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			new_len;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen_gnl(s))
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	new_len = ft_strlen_gnl(s + start);
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
