/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:37:43 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/20 13:18:06 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <sys/time.h>
#include <unistd.h>

uint64_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0) == -1)
		return (error("gettimeofday failed"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void		ft_usleep(t_data *data)
{
	uint64_t	time;

	time = gettime();
	while ((int)(gettime() - time) <= data->time_to_sleep)
		usleep(100);
}
