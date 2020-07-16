/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 14:01:02 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/07/16 13:15:46 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

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

void	*check_philo(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo*)ptr;
	while (!philo->po->died)
	{
		if (pthread_mutex_lock(&philo->is_eating))
			return (0);
		if (gettime() - philo->last_meal > philo->po->time_to_die)
		{
			status(philo, 4);
			philo->po->died = 1;
			return (0);
		}
		if (pthread_mutex_unlock(&philo->is_eating))
			return (0);
		usleep(500);
	}
	return (0);
}

int		check_meals(t_data *po)
{
	int		i;
	int		j;

	if (po->died == 1)
		return (1);
	i = 0;
	j = 0;
	if (po->must_eat > 0)
	{
		while (i < po->peeps)
		{
			if (po->philo[i].meals >= po->must_eat)
			{
				j++;
				if (j == po->peeps)
				{
					status(&po->philo[0], 5);
					po->died = 1;
					return (1);
				}
			}
			i++;
		}
	}
	return (0);
}
