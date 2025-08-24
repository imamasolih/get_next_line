/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imamasol <imamasol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:05:12 by imamasol          #+#    #+#             */
/*   Updated: 2025/08/24 15:07:40 by imamasol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_freestash(char **stash)
{
	free(*stash);
	*stash = NULL;
	return (NULL);
}

size_t	ft_strlen(const char *c)
{
	size_t	n;

	n = 0;
	while (c[n])
		n++;
	return (n);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == 0)
		return ((char *)str);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src && n > 0)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_append(char **stash, const char *buf)
{
	char	*tmp;
	size_t	len_buf;
	size_t	len_stash;

	if (!*stash)
		len_stash = 0;
	else
		len_stash = ft_strlen(*stash);
	if (!buf)
		return (*stash);
	len_buf = ft_strlen(buf);
	if (len_buf == 0)
		return (*stash);
	if (len_stash > SIZE_MAX - (len_buf + 1))
		return (ft_freestash(stash));
	tmp = malloc(len_stash + len_buf + 1);
	if (!tmp)
		return (ft_freestash(stash));
	if (len_stash)
		ft_memcpy(tmp, *stash, len_stash);
	ft_memcpy(tmp + len_stash, buf, len_buf);
	tmp[len_stash + len_buf] = '\0';
	free(*stash);
	return (tmp);
}
