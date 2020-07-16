/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/11 12:53:55 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/07/11 12:58:46 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/time.h>

uint64_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0 == -1))
		return (error("gettimeofday failed"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}