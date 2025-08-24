/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imamasol <imamasol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:45:45 by imamasol          #+#    #+#             */
/*   Updated: 2025/08/23 19:53:09 by imamasol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_freestash(char **stash)
{
	free(*stash);
	*stash = NULL;
	return (NULL);
}

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

static char	*ft_newline(char **stash, const char *srch)
{
	char	*line;
	char	*leftover;
	size_t	linelen;
	size_t	restlen;

	linelen = (srch - *stash) + 1;
	line = malloc(linelen + 1);
	if (!line)
		return (ft_freestash(stash));
	ft_memcpy(line, *stash, linelen);
	line[linelen] = '\0';
	restlen = ft_strlen(*stash) - linelen;
	leftover = malloc(restlen + 1);
	if (!leftover)
	{
		free(line);
		return (ft_freestash(stash));
	}
	if (restlen)
		ft_memcpy(leftover, srch + 1, restlen);
	leftover[restlen] = '\0';
	free(*stash);
	*stash = leftover;
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
			return (ft_free(stash));
		if (byte == 0)
			return (ft_zerobyte(&stash));
		buffer[byte] = '\0';
		stash = ft_append(stash, buffer);
		if (!stash)
			return (NULL);
	}
}
