/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 15:57:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/21 13:27:48 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>
#include <stdlib.h>

void	cleanup(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->no_philos)
	{
		sem_post(data->philo[i].is_eating);
		sem_post(data->forks);
		i++;
	}
	sem_post(data->is_writing);
	usleep(data->no_philos * 100);
	i = 0;
	while (i < data->no_philos)
	{
		sem_close(data->philo[i].is_eating);
		i++;
	}
	sem_close(data->is_writing);
	sem_close(data->forks);
	free(data->philo);
}

int		status(t_philo *philo, char *str)
{
	if (philo->data->stop)
		return (0);
	if (sem_wait(philo->data->is_writing) < 0)
		return (0);
	if (philo->data->stop)
		return (0);
	ft_putnbr(gettime() - philo->data->start_time);
	write(1, " ", 1);
	if (str[0] == 'e' && str[1] == '\0')
	{
		ft_putstr("All philosophers have eaten enough\n");
		return (0);
	}
	ft_putnbr(philo->nb);
	if (str[0] == '\0')
	{
		ft_putstr(" died\n");
		return (0);
	}
	ft_putstr(str);
	if (philo->data->stop)
		return (0);
	sem_post(philo->data->is_writing);
	return (1);
}

void	eat(t_philo *philo)
{
	if (!philo->data->stop)
		if (sem_wait(philo->data->forks) < 0)
			return ;
	if (!status(philo, " has taken a fork\n"))
		return ;
	if (sem_wait(philo->data->forks) < 0)
		return ;
	if (!status(philo, " has taken a fork\n"))
		return ;
	if (sem_wait(philo->is_eating) < 0)
		return ;
	if (!status(philo, " is eating\n"))
		return ;
	philo->last_eaten = gettime();
	philo->times_eaten++;
	if (!philo->data->stop)
		if (sem_post(philo->is_eating) < 0)
			return ;
	usleep(1000 * philo->data->time_to_eat);
	if (!philo->data->stop)
		if (sem_post(philo->data->forks) < 0)
			return ;
	if (philo->data->stop)
		return ;
	sem_post(philo->data->forks);
}

void	*run(void *ptr)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)ptr;
	if (pthread_create(&tid, NULL, &check_health, ptr))
	{
		error("failed pthread");
		return (NULL);
	}
	if (pthread_detach(tid))
	{
		error("failed pthread");
		return (NULL);
	}
	while (!philo->data->stop)
	{
		eat(philo);
		if (!status(philo, " is sleeping\n"))
			break ;
		ft_usleep(philo->data);
		status(philo, " is thinking\n");
	}
	return (0);
}

int		start(t_data *data)
{
	int			i;
	int			check;
	pthread_t	tid;

	i = 0;
	data->start_time = gettime();
	while (i < data->no_philos)
	{
		check = pthread_create(&tid, NULL, &run, &data->philo[i]);
		data->philo[i].last_eaten = gettime();
		if (check || pthread_detach(tid))
		{
			free(data->philo);
			return (error("failed pthread"));
		}
		usleep(100);
		i++;
	}
	while (!check_meals(data))
		usleep(500);
	cleanup(data);
	return (0);
}
