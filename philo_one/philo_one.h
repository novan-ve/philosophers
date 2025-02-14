/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:16:09 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/20 12:58:46 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdint.h>

typedef struct		s_philo
{
	int				nb;
	int				left;
	int				right;
	int				times_eaten;
	uint64_t		last_eaten;
	pthread_mutex_t	is_eating;
	struct s_data	*data;
}					t_philo;

typedef	struct		s_data
{
	t_philo			*philo;
	int				no_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				amount_to_eat;
	int				stop;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_writing;
}					t_data;

int					start(t_data *data);
void				status(t_philo *philo, char *str);
void				*check_health(void *ptr);
int					check_meals(t_data *data);

int					error(char *s);
int					ft_atoi(const char *str);
void				ft_putchar(char c);
void				ft_putnbr(uint64_t n);
void				ft_putstr(char *s);
uint64_t			gettime(void);
void				ft_usleep(t_data *data);

#endif
