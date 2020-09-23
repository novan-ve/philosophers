/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 13:43:02 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/08/01 12:12:55 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>

void	status(t_philo *philo, int x)
{
	if (sem_wait(philo->po->is_writing) < 0)
		return ;
	ft_putnbr(gettime() - philo->po->start_time);
	write(1, " ", 1);
	if (x == 5)
	{
		ft_putstr("All philosophers have eaten specified amount\n");
		return ;
	}
	ft_putnbr(philo->pos);
	if (x == 4)
	{
		ft_putstr(" died\n");
		return ;
	}
	if (x == 0)
		ft_putstr(" has taken a fork\n");
	if (x == 1)
		ft_putstr(" is eating\n");
	if (x == 2)
		ft_putstr(" is sleeping\n");
	if (x == 3)
		ft_putstr(" is thinking\n");
	if (sem_post(philo->po->is_writing) < 0)
		return ;
}
