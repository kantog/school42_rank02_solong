# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:15:35 by bclaeys           #+#    #+#              #
#    Updated: 2024/08/26 15:11:03 by bclaeys          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a 
TESTFILE=test
CODEDIRS=.
INCDIRS=.
CFILES=ft_format.c ft_printf.c ftpr_putchar.c ftpr_puthex.c ftpr_putint.c ftpr_putstr.c ftpr_putptr.c ftpr_putunsdec.c get_next_line_utils.c get_next_line.c ft_strrchr.c

OPT=-O0
CC=cc
CFLAGS=-Wall -Wextra -Werror -g
OBJECTS=$(patsubst %.c,%.o,$(CFILES))

all: $(NAME)
	
$(NAME): $(OBJECTS)
	@ar rcs $@ $^
	@echo "Making libft"

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<
# < Verwijst maar naar een enkele dependency.
	
clean:
	@rm -f $(OBJECTS) $(DEPFILES) $(TESTFILE)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
