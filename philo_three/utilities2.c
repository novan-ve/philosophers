/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/11 12:53:55 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/20 17:42:47 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
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
	uint64_t		time;

	time = gettime();
	while ((gettime() - time) <= data->time_to_sleep)
		usleep(100);
}
