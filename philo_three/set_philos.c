/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_philos.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 12:34:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/08/01 13:06:43 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>
#include <fcntl.h>

int		sem_fail(t_data *po)
{
	free(po->philo);
	free(po->proc);
	return (error("sem_open failed"));
}

int		set_data(t_data *po)
{
	int		i;

	i = 0;
	while (i < po->peeps)
	{
		sem_unlink("/is_eating");
		po->philo[i].is_eating = sem_open("/is_eating", O_CREAT | O_EXCL, \
		0666, 1);
		if (po->philo[i].is_eating == SEM_FAILED)
			return (sem_fail(po));
		sem_unlink("/done_eating");
		po->philo[i].done_eating = sem_open("/done_eating", O_CREAT | O_EXCL, \
		0666, 0);
		if (po->philo[i].done_eating == SEM_FAILED)
			return (sem_fail(po));
		po->philo[i].meals = 0;
		po->philo[i].pos = i + 1;
		po->philo[i].po = po;
		i++;
	}
	return (1);
}

int		set_philos(t_data *po)
{
	po->philo = (t_philo*)malloc(sizeof(t_philo) * po->peeps);
	if (!po->philo)
		return (error("malloc failed"));
	po->proc = (pid_t*)malloc(sizeof(pid_t) * po->peeps);
	if (!po->proc)
	{
		free(po->philo);
		return (error("malloc failed"));
	}
	sem_unlink("/sema");
	sem_unlink("/is_writing");
	sem_unlink("/end_simulation");
	po->is_writing = sem_open("/is_writing", O_CREAT | O_EXCL, 0666, 1);
	if (po->is_writing == SEM_FAILED)
		return (sem_fail(po));
	po->sema = sem_open("/sema", O_CREAT | O_EXCL, 0666, po->peeps);
	if (po->sema == SEM_FAILED)
		return (sem_fail(po));
	po->end = sem_open("/end_simulation", O_CREAT | O_EXCL, 0666, 0);
	if (po->end == SEM_FAILED)
		return (sem_fail(po));
	set_data(po);
	return (1);
}
