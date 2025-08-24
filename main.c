#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// cc -Wall -Wextra -Werror main.c get_next_line.a -o gnl_run
// ./gnl_run

static void	test_run_txt(void)
{
	int		fd;
	char	*line;
	int	i;

	fd = open("run.txt", O_RDONLY);
	i = 0;
	if (fd < 0)
	{
		perror("open run.txt");
		return ;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("L%d: %s", ++i, line);
		free(line);
	}
	close(fd);
}

int	main(void)
{
	test_run_txt();
	return (0);
}
