/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:13:10 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/21 12:51:32 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdlib.h>

int		init_philo(t_data *data)
{
	int		i;
	int		check;

	i = 0;
	while (i < data->no_philos)
	{
		check = pthread_mutex_init(&data->philo[i].is_eating, NULL);
		if (check || pthread_mutex_init(&data->forks[i], NULL))
		{
			free(data->forks);
			free(data->philo);
			return (error("Failed initializing mutex"));
		}
		data->philo[i].nb = i + 1;
		data->philo[i].left = i;
		data->philo[i].right = (i + 1) % data->no_philos;
		data->philo[i].times_eaten = 0;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

int		init_data(t_data *data)
{
	int		nb;

	if (pthread_mutex_init(&data->is_writing, NULL))
		return (error("Failed initializing mutex"));
	data->philo = (t_philo*)malloc(sizeof(t_philo) * data->no_philos);
	if (!data->philo)
		return (error("malloc fail"));
	nb = data->no_philos;
	data->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * nb);
	if (!data->forks)
	{
		free(data->philo);
		return (error("malloc fail"));
	}
	data->stop = 0;
	return (init_philo(data));
}

int		set_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error("wrong amount of arguments"));
	data->no_philos = ft_atoi(av[1]);
	if (!data->no_philos)
		return (error("number of philosophers can't be 0"));
	data->time_to_die = ft_atoi(av[2]);
	if (!data->time_to_die)
		return (error("time_to_die can't be 0"));
	data->time_to_eat = ft_atoi(av[3]);
	if (!data->time_to_eat)
		return (error("time_to_eat can't be 0"));
	data->time_to_sleep = ft_atoi(av[4]);
	if (!data->time_to_sleep)
		return (error("time_to_sleep can't be 0"));
	if (ac == 6)
	{
		data->amount_to_eat = ft_atoi(av[5]);
		if (!data->amount_to_eat)
			return (error("number of times to eat can't be 0"));
	}
	else
		data->amount_to_eat = 0;
	return (1);
}

int		main(int ac, char **av)
{
	t_data		data;

	if (!set_data(&data, ac, av))
		return (0);
	if (!init_data(&data))
		return (0);
	return (start(&data));
}
