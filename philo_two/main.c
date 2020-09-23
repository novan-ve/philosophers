/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:13:10 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/21 12:50:16 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdlib.h>

int		init_philo(t_data *data)
{
	int		i;

	i = 0;
	sem_unlink("/is_eating");
	while (i < data->no_philos)
	{
		data->philo[i].is_eating = sem_open("/is_eating", O_CREAT, 0666, 1);
		if (data->philo[i].is_eating == SEM_FAILED)
		{
			free(data->philo);
			return (error("Failed opening semaphore"));
		}
		data->philo[i].nb = i + 1;
		data->philo[i].times_eaten = 0;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

int		init_data(t_data *data)
{
	sem_unlink("/is_writing");
	data->is_writing = sem_open("/is_writing", O_CREAT, 0666, 1);
	if (data->is_writing == SEM_FAILED)
		return (error("Failed opening semaphore"));
	data->philo = (t_philo*)malloc(sizeof(t_philo) * data->no_philos);
	if (!data->philo)
		return (error("malloc fail"));
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, 0666, data->no_philos);
	if (data->forks == SEM_FAILED)
	{
		free(data->philo);
		return (error("Failed opening semaphore"));
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
