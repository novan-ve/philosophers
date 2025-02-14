/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 15:57:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/21 12:59:39 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdlib.h>

void	status(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(&philo->data->is_writing))
		return ;
	ft_putnbr(gettime() - philo->data->start_time);
	write(1, " ", 1);
	if (str[0] == 'e' && str[1] == '\0')
	{
		ft_putstr("All philosophers have eaten enough\n");
		return ;
	}
	ft_putnbr(philo->nb);
	if (str[0] == '\0')
	{
		ft_putstr(" died\n");
		return ;
	}
	ft_putstr(str);
	pthread_mutex_unlock(&philo->data->is_writing);
}

void	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->left]))
		return ;
	status(philo, " has taken a fork\n");
	if (pthread_mutex_lock(&philo->data->forks[philo->right]))
		return ;
	status(philo, " has taken a fork\n");
	if (pthread_mutex_lock(&philo->is_eating))
		return ;
	status(philo, " is eating\n");
	philo->last_eaten = gettime();
	philo->times_eaten++;
	if (pthread_mutex_unlock(&philo->is_eating))
		return ;
	usleep(1000 * philo->data->time_to_eat);
	if (pthread_mutex_unlock(&philo->data->forks[philo->right]))
		return ;
	pthread_mutex_unlock(&philo->data->forks[philo->left]);
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
		status(philo, " is sleeping\n");
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
			free(data->forks);
			free(data->philo);
			return (error("failed pthread"));
		}
		usleep(100);
		i++;
	}
	while (!check_meals(data))
		usleep(500);
	free(data->forks);
	free(data->philo);
	return (0);
}
