      # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/16 11:22:10 by lucinguy          #+#    #+#              #
#    Updated: 2025/12/16 16:53:58 by lucinguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := pipex
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
RM      := rm -f
LIBFT_DIR := libft
LIBFT   := $(LIBFT_DIR)/libft.a
INCS    := -I. -I./$(LIBFT_DIR)

# ----------------------------- Mandatory ----------------------------- #
SRCS := \
	pipex.c \
	utils.c \
	exec.c

OBJS := $(SRCS:.c=.o)

# ----------------------------- Rules ----------------------------- #
all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re