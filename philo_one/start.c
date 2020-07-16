/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 13:38:13 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/07/16 13:35:38 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdlib.h>
#include <unistd.h>

void	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->po->mutex[philo->left]))
		return ;
	status(philo, 0);
	if (pthread_mutex_lock(&philo->po->mutex[philo->right]))
		return ;
	status(philo, 0);
	if (pthread_mutex_lock(&philo->is_eating))
		return ;
	status(philo, 1);
	philo->last_meal = gettime();
	philo->meals++;
	if (pthread_mutex_unlock(&philo->is_eating))
		return ;
	usleep(1000 * philo->po->time_to_eat);
	if (pthread_mutex_unlock(&philo->po->mutex[philo->left]))
		return ;
	if (pthread_mutex_unlock(&philo->po->mutex[philo->right]))
		return ;
}

void	*start_philo(void *ptr)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)ptr;
	if (pthread_create(&tid, NULL, &check_philo, ptr))
		return (0);
	if (pthread_detach(tid))
		return (0);
	while (!philo->po->died)
	{
		eat(philo);
		status(philo, 2);
		usleep(1000 * philo->po->time_to_sleep);
		status(philo, 3);
	}
	return (0);
}

int		start(t_data *po)
{
	int			i;
	int			check;
	pthread_t	tid;

	po->start_time = gettime();
	i = 0;
	while (i < po->peeps)
	{
		check = pthread_create(&tid, NULL, &start_philo, &po->philo[i]);
		po->philo[i].last_meal = gettime();
		if (check || pthread_detach(tid))
		{
			free(po->mutex);
			free(po->philo);
			return (error("failed pthread"));
		}
		usleep(100);
		i++;
	}
	while (!check_meals(po))
		usleep(100);
	free(po->philo);
	free(po->mutex);
	return (1);
}
