/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 10:20:55 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/07/11 13:34:27 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>

typedef struct		s_philo
{
	int				pos;
	int				eating;
	int				left;
	int				right;
	int				meals;
	uint64_t		last_meal;
	pthread_mutex_t	is_eating;
	struct s_data	*po;
}					t_philo;

typedef	struct		s_data
{
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	is_writing;
	int				peeps;
	int				must_eat;
	int				died;
	uint64_t		start_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
}					t_data;

int					check(t_data *po, int ac, char **av);
void				*check_philo(void *ptr);
int					check_meals(t_data *po);

int					set_philos(t_data *po);

int					start(t_data *po);

int					error(char *s);
int					ft_atoi(const char *str);
void				ft_putstr(char *s);
void				ft_putnbr(uint64_t n);
void				ft_putchar(char c);
uint64_t			gettime(void);

void				status(t_philo *philo, int x);

#endif