# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imamasol <imamasol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/24 14:35:23 by imamasol          #+#    #+#              #
#    Updated: 2025/08/24 19:28:18 by imamasol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
SRCS = get_next_line.c  get_next_line_utils.c
SRCS_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

AR      = ar
ARFLAGS = rcs
CC		= cc
RM      = rm -f
OBJS	= $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror

BUFFER_SIZE ?= 42
CFLAGS += -DBUFFER_SIZE=$(BUFFER_SIZE)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

get_next_line_bonus.o: get_next_line_bonus.c get_next_line_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

get_next_line_utils_bonus.o: get_next_line_utils_bonus.c get_next_line_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $^
	
clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re