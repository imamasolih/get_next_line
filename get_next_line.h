/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imamasol <imamasol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:55:49 by imamasol          #+#    #+#             */
/*   Updated: 2025/08/24 15:07:43 by imamasol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *c);
char	*ft_freestash(char **stash);
char	*ft_strchr(const char *str, int c);
char	*ft_append(char **stash, const char *buf);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif