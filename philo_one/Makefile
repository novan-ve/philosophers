# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <novan-ve@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/16 13:55:50 by novan-ve      #+#    #+#                  #
#    Updated: 2020/09/16 16:39:02 by novan-ve      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJ = main.o start.o check.o utils.o utils2.o

DEPS = philo_one.h

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
