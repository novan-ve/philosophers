/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_philos.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 12:34:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/07/11 14:39:13 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdlib.h>

int		set_philos(t_data *po)
{
	int		i;

	po->philo = (t_philo*)malloc(sizeof(t_philo) * po->peeps);
	if (!po->philo)
		return (error("malloc failed"));
	po->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * po->peeps); 
	if (!po->mutex)
	{
		free(po->philo);
		return (error("malloc failed"));
	}
	i = 0;
	while (i < po->peeps)
	{
		if (pthread_mutex_init(&po->mutex[i], NULL))
		{
			free(po->philo);
			free(po->mutex);
			return (error("mutex init failed"));
		}
		po->philo[i].meals = 0;
		po->philo[i].eating = 0;
		po->philo[i].left = i;
		po->philo[i].right = (i + 1) % po->peeps;
		po->philo[i].pos = i + 1;
		po->philo[i].po = po;
		po->philo[i].last_meal = 0;
		if (pthread_mutex_init(&po->philo[i].is_eating, 0))
		{
			free(po->philo);
			free(po->mutex);
			return (error("mutex init failed"));
		}
		i++;
	}
	po->died = 0;
	if (pthread_mutex_init(&po->is_writing, 0))
	{
		free(po->philo);
		free(po->mutex);
		return (error("mutex init failed"));
	}
	return (1);
}
