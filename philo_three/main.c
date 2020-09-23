/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 10:12:53 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/21 13:36:45 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_data			po;

	if (!check(&po, ac, av))
		return (1);
	if (!set_philos(&po))
		return (1);
	if (!start(&po))
		return (1);
	return (0);
}
