/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imamasol <imamasol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:45:45 by imamasol          #+#    #+#             */
/*   Updated: 2025/08/24 19:33:25 by imamasol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static int	ft_readbuf(int fd, char **stash)
{
	int		ret;
	ssize_t	byte;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	byte = read(fd, buffer, BUFFER_SIZE);
	ret = 1;
	if (byte < 0)
		ret = -1;
	else if (byte == 0)
		ret = 0;
	else
	{
		buffer[byte] = '\0';
		if (ft_strchr(buffer, '\n'))
			ret = 2;
		if (!ft_append(stash, buffer))
			ret = -1;
	}
	free(buffer);
	return (ret);
}

char	*get_next_line(int fd)
{
	int			index;
	char		*srch;
	static char	*stash[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash[fd])
	{
		srch = ft_strchr(stash[fd], '\n');
		if (srch)
			return (ft_newline(&stash[fd], srch));
	}
	while (1)
	{
		index = ft_readbuf(fd, &stash[fd]);
		if (index < 0)
			return (ft_freestash(&stash[fd]));
		if (index == 0)
			return (ft_zerobyte(&stash[fd]));
		if (index == 2)
		{
			srch = ft_strchr(stash[fd], '\n');
			return (ft_newline(&stash[fd], srch));
		}
	}
}
