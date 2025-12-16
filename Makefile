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
AR      := ar rcs
RM      := rm -f

INCS    := -I. -Ilibft

# ----------------------------- Mandatory ----------------------------- #

SRCS := \
	pipex.c \
	utils.c

# ----------------------------- Bonus ----------------------------- #

BSRCS := \

OBJS := $(SRCS:.c=.o)
BOBJS := $(BSRCS:.c=.o)

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o pipex

# bonus: $(LIBFT) $(NAME) $(BOBJS)
# 	$(AR) $(NAME) $(BOBJS)

clean:
	$(RM) $(OBJS) $(BOBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) pipex
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus