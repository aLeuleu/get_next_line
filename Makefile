# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 20:55:17 by alevra            #+#    #+#              #
#    Updated: 2022/11/12 10:02:24 by alevra           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line

HEADER = get_next_line.h

SRC =	ft_memset.c		\

BONUS_SRC =	

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

all	: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)


bonus: $(BONUS_OBJ)

%.o : %.c $(HEADER)
	gcc -c -Wall -Wextra -Werror $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus all
