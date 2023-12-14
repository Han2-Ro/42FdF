# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 22:50:02 by hrother           #+#    #+#              #
#    Updated: 2023/12/14 21:50:11 by hrother          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -pg -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = objs
SRCS = main.c render.c utils.c handle_input.c init_map.c transform.c key_handler.c hooks.c
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
NAME = fdf
RM = rm -fr

all: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft -lft -L./minilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./libft
	$(RM) $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re