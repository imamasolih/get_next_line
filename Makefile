# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imamasol <imamasol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/24 14:35:23 by imamasol          #+#    #+#              #
#    Updated: 2025/08/24 15:07:46 by imamasol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SRCS = get_next_line.c  get_next_line_utils.c 

AR      = ar
ARFLAGS = rcs
CC		= cc
RM      = rm -f
OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror

BUFFER_SIZE ?= 42
CFLAGS += -DBUFFER_SIZE=$(BUFFER_SIZE)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re