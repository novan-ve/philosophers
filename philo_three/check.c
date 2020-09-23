/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 14:01:02 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/21 13:34:13 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int		check(t_data *po, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error("wrong amount of arguments"));
	po->peeps = ft_atoi(av[1]);
	if (!po->peeps)
		return (error("number of philosophers can't be 0"));
	po->time_to_die = ft_atoi(av[2]);
	if (!po->time_to_die)
		return (error("time to die can't be 0"));
	po->time_to_eat = ft_atoi(av[3]);
	if (!po->time_to_eat)
		return (error("time to eat can't be 0"));
	po->time_to_sleep = ft_atoi(av[4]);
	if (!po->time_to_sleep)
		return (error("time to sleep can't be 0"));
	if (ac == 6)
	{
		po->must_eat = ft_atoi(av[5]);
		if (!po->must_eat)
			return (error("no of time philos must eat can't be 0"));
	}
	return (1);
}

void	*check_meals(void *ptr)
{
	t_data		*po;
	int			i;

	i = 0;
	po = (t_data*)ptr;
	while (i < po->peeps)
	{
		sem_wait(po->philo[i].done_eating);
		i++;
	}
	status(&po->philo[i - 1], 5);
	sem_post(po->end);
	return ((void*)0);
}

void	check_simulation(t_data *po)
{
	pthread_t	pid;

	if (pthread_create(&pid, 0, &check_meals, (void*)po))
	{
		error("pthread_create failed");
		kill_proc(po);
		exit(1);
	}
	if (pthread_detach(pid))
	{
		error("pthread_detach failed");
		kill_proc(po);
		exit(1);
	}
}

void	*check_philo(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo*)ptr;
	while (1)
	{
		if (sem_wait(philo->is_eating) < 0)
			return ((void*)0);
		if (gettime() - philo->last_meal > philo->po->time_to_die)
		{
			sem_post(philo->po->end);
			status(philo, 4);
			return ((void*)0);
		}
		if (sem_post(philo->is_eating) < 0)
			return ((void*)0);
		if (philo->po->must_eat > 0)
			if (philo->meals >= philo->po->must_eat)
				sem_post(philo->done_eating);
		usleep(500);
	}
	return ((void*)0);
}
