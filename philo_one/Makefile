# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <novan-ve@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/29 12:38:40 by novan-ve      #+#    #+#                  #
#    Updated: 2020/07/11 12:57:46 by novan-ve      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 			philo_one

SRC = 			main.c \
				check.c \
				set_philos.c \
				start.c \
				status.c \
				utilities.c \
				utilities2.c

OBJS =			$(SRCS:.c=.o)

FLAGS = 		-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(SRC) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
