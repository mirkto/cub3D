# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 22:44:15 by ngonzo            #+#    #+#              #
#    Updated: 2020/10/28 22:44:18 by ngonzo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
FLAGS = -Wall -Werror -Wextra -g
SRCS = 	src/main.c src/parser.c src/errors.c src/screenshot.c src/sprite.c\
		src/move.c src/inits.c src/parser_map.c src/parser_config.c\
		src/utils.c src/raycast.c src/raycast_two.c
OBJS = $(SRCS:c=o)
LIBFT = ./libs/libft/libft.a
MLX = libmlx.dylib -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libs/libft

$(MLX):
	$(MAKE) -C ./libs/minilibx_mms
	mv ./libs/minilibx_mms/libmlx.dylib ./

$(OBJS): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) fclean -C ./libs/libft
	$(MAKE) clean -C ./libs/minilibx_mms

fclean: clean
	rm -rf $(NAME)
	rm -rf screenshot.bmp
	rm -rf libmlx.dylib
	$(MAKE) fclean -C ./libs/libft

re: fclean all

.PHONY: all, clean, fclean, re