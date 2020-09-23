/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 16:38:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/20 13:15:33 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void	*check_health(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo*)ptr;
	while (!philo->data->stop)
	{
		if (pthread_mutex_lock(&philo->is_eating))
			return (0);
		if ((int)(gettime() - philo->last_eaten) > philo->data->time_to_die)
		{
			status(philo, "");
			philo->data->stop = 1;
			return (0);
		}
		if (pthread_mutex_unlock(&philo->is_eating))
			return (0);
		usleep(500);
	}
	return (0);
}

int		check_meals(t_data *data)
{
	int		i;
	int		j;

	if (data->stop == 1)
		return (1);
	i = 0;
	j = 0;
	if (data->amount_to_eat > 0)
	{
		while (i < data->no_philos)
		{
			if (data->philo[i].times_eaten >= data->amount_to_eat)
			{
				j++;
				if (j == data->no_philos)
				{
					status(&data->philo[i], "e");
					data->stop = 1;
					return (1);
				}
			}
			i++;
		}
	}
	return (0);
}
