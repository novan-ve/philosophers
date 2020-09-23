/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <novan-ve@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:37:38 by novan-ve      #+#    #+#                 */
/*   Updated: 2020/09/16 14:37:39 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>

int						error(char *s)
{
	int					i;
	char				ch;

	i = 0;
	write(1, "Error: ", 7);
	while (s[i])
	{
		ch = s[i];
		write(1, &ch, 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int						ft_atoi(const char *str)
{
	int					factor;
	unsigned long long	result;
	unsigned long long	max;
	int					i;

	max = 9223372036854775807;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' && str[i + 1] != '+' && str[i + 1] != '-')
		i++;
	factor = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (factor == -1 && result > max)
			return (0);
		if (result > max)
			return (-1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (factor * (int)result);
}

void					ft_putchar(char c)
{
	write(1, &c, 1);
}

void					ft_putnbr(uint64_t n)
{
	char				*radix;

	radix = "0123456789";
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(radix[n % 10]);
}

void					ft_putstr(char *s)
{
	char				ch;

	while (*s)
	{
		ch = *s;
		write(1, &ch, 1);
		s++;
	}
}
