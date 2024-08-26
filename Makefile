# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 12:39:18 by bclaeys           #+#    #+#              #
#    Updated: 2024/08/25 19:29:17 by bclaeys          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=so_long
CFILES=src/so_long.c src/sl_utils.c src/sl_flooder.c src/sl_create_map.c src/sl_free_all.c
CC=cc
CFLAGS= -Wall -Wextra -Werror -g
INCFLAGS= -L minilibx-linux -lmlx_Linux -lmlx -I minilibx_linux -lXext -lX11 -lm -lz -I libft -L libft -lft
INCLUDES = -I ./libft -I ./mlx
MLX=./minilibx-linux/libmlx_Linux.a
LIBFT=./libft/libft.a
OBJECTS=$(patsubst src/%.c,obj/%.o,$(CFILES))

all: $(LIBFT) $(MLX) obj $(NAME)
	
$(LIBFT):
	@echo "\033[33m[ .. ] | Compiling libft...\033[0m"
	@make -s -C libft 	
	@echo "\033[33m[OK] | libft ready!\033"

$(MLX):
	@echo "\033[33m[ ... ] | Compiling mlx..\033[0m"
	@make -s -C minilibx-linux 	
	@echo "\033[33m[OK] | mlx ready\033[0m"

$(NAME): $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(INCFLAGS)
	@echo "\033[33mso_long created\033[0m"

obj: 
	@mkdir -p obj

obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	@rm -f $(OBJECTS)
	@if [ -d "obj" ]; then rmdir obj/; \
	fi
	@make -s $@ -C libft
	@make -s $@ -C minilibx-linux 
	@echo "\033[33mAll object files, dependency files, archive files and test files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[33mBinary removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re test libft mlx obj
