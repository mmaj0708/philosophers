# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 09:09:37 by mmaj              #+#    #+#              #
#    Updated: 2021/03/02 11:23:06 by mmaj             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRCS = srcs/checker.c srcs/main.c srcs/philo_life.c srcs/parsing.c \
	srcs/init_philo.c srcs/utils.c srcs/philo_action.c

OBJECTS = $(SRCS:.c=.o)

INCLUDES = ./philosophers.h

all : $(NAME)

$(NAME) : $(OBJECTS)

	gcc -Wall -Wextra -Werror -o ${NAME} $(OBJECTS)

clean : 
	@/bin/rm -f $(OBJECTS)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
