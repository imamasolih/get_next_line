/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imamasol <imamasol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:45:45 by imamasol          #+#    #+#             */
/*   Updated: 2025/08/24 15:07:36 by imamasol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_zerobyte(char **stash)
{
	char	*leftline;

	if (*stash && **stash)
	{
		leftline = *stash;
		*stash = NULL;
		return (leftline);
	}
	return (NULL);
}

static int	ft_leftover(char **stash, const char *start, size_t restlen)
{
	char	*leftover;

	leftover = malloc(restlen + 1);
	if (!leftover)
		return (0);
	ft_memcpy(leftover, start, restlen);
	leftover[restlen] = '\0';
	free(*stash);
	*stash = leftover;
	return (1);
}

static char	*ft_newline(char **stash, const char *srch)
{
	char	*line;
	size_t	linelen;
	size_t	restlen;

	linelen = (size_t)(srch - *stash) + 1;
	line = malloc(linelen + 1);
	if (!line)
		return (ft_freestash(stash));
	ft_memcpy(line, *stash, linelen);
	line[linelen] = '\0';
	restlen = ft_strlen(*stash) - linelen;
	if (restlen == 0)
	{
		ft_freestash(stash);
		return (line);
	}
	if (!ft_leftover(stash, srch + 1, restlen))
	{
		free(line);
		return (ft_freestash(stash));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t		byte;
	char		*srch;
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (stash)
		{
			srch = ft_strchr(stash, '\n');
			if (srch)
				return (ft_newline(&stash, srch));
		}
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte < 0)
			return (ft_freestash(&stash));
		if (byte == 0)
			return (ft_zerobyte(&stash));
		buffer[byte] = '\0';
		stash = ft_append(&stash, buffer);
		if (!stash)
			return (NULL);
	}
}
