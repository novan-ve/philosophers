/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 13:38:13 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/21 13:35:39 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void	cleanup(t_data *po)
{
	int		i;

	i = 0;
	while (i < po->peeps)
	{
		sem_post(po->philo[i].is_eating);
		sem_post(po->sema);
		i++;
	}
	i = 0;
	while (i < po->peeps)
	{
		sem_close(po->philo[i].is_eating);
		i++;
	}
	sem_close(po->is_writing);
	sem_close(po->sema);
	sem_close(po->end);
}

void	kill_proc(t_data *po)
{
	int		i;

	i = 0;
	while (i < po->peeps)
	{
		kill(po->proc[i], SIGKILL);
		i++;
	}
}

void	eat(t_philo *philo)
{
	if (sem_wait(philo->po->sema) < 0)
		return ;
	status(philo, 0);
	if (sem_wait(philo->po->sema) < 0)
		return ;
	status(philo, 0);
	if (sem_wait(philo->is_eating) < 0)
		return ;
	status(philo, 1);
	philo->last_meal = gettime();
	philo->meals++;
	if (sem_post(philo->is_eating) < 0)
		return ;
	usleep(1000 * philo->po->time_to_eat);
	if (sem_post(philo->po->sema) < 0)
		return ;
	if (sem_post(philo->po->sema) < 0)
		return ;
}

void	start_philo(t_philo *philo)
{
	pthread_t	pid;

	if (pthread_create(&pid, 0, &check_philo, (void*)philo))
	{
		error("pthread_create failed");
		exit(1);
	}
	if (pthread_detach(pid))
	{
		error("pthread_detach failed");
		exit(1);
	}
	while (1)
	{
		eat(philo);
		status(philo, 2);
		ft_usleep(philo->po);
		status(philo, 3);
	}
}

int		start(t_data *po)
{
	int			i;

	po->start_time = gettime();
	i = 0;
	while (i < po->peeps)
	{
		po->philo[i].last_meal = gettime();
		po->proc[i] = fork();
		if (po->proc[i] < 0)
		{
			error("Creating process failed");
			kill_proc(po);
			return (0);
		}
		else if (po->proc[i] == 0)
			start_philo(&po->philo[i]);
		usleep(100);
		i++;
	}
	check_simulation(po);
	sem_wait(po->end);
	kill_proc(po);
	cleanup(po);
	return (1);
}
