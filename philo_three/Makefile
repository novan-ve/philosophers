# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <novan-ve@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/16 13:55:50 by novan-ve      #+#    #+#                  #
#    Updated: 2020/09/20 17:42:21 by novan-ve      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJ = main.o check.o set_philos.o start.o status.o utilities.o utilities2.o

DEPS = philo_three.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lpthread

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
