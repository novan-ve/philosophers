/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 10:12:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/07/02 14:08:18 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/time.h>

int		main(int ac, char **av)
{
	t_data			po;

	if (!check(&po, ac, av))
		return (0);
	if (!set_philos(&po))
		return (0);
	if (!start(&po))
		return (0);
	return (0);
}
