/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 10:20:55 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/20 17:39:46 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <semaphore.h>
# include <stdint.h>

typedef struct		s_philo
{
	int				pos;
	int				meals;
	uint64_t		last_meal;
	sem_t			*is_eating;
	sem_t			*done_eating;
	struct s_data	*po;
}					t_philo;

typedef	struct		s_data
{
	t_philo			*philo;
	pid_t			*proc;
	sem_t			*sema;
	sem_t			*is_writing;
	sem_t			*end;
	int				peeps;
	int				must_eat;
	uint64_t		start_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
}					t_data;

int					check(t_data *po, int ac, char **av);
void				*check_philo(void *ptr);
void				*check_meals(void *ptr);
void				check_simulation(t_data *po);

int					set_philos(t_data *po);

int					start(t_data *po);
void				kill_proc(t_data *po);

int					error(char *s);
int					ft_atoi(const char *str);
void				ft_putstr(char *s);
void				ft_putnbr(uint64_t n);
void				ft_putchar(char c);
uint64_t			gettime(void);
void				ft_usleep(t_data *data);

void				status(t_philo *philo, int x);

#endif
