/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:53:35 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/20 11:54:39 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	long long	sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
		if (*str == '+' || *str == '-')
			return (0);
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

int	is_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	validate_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments\n"), 0);
	if (ft_atoi(argv[1]) < 1 && ft_atoi(argv[1]) > MAX_PHILOS)
		return (printf("Error: Num of philos must be between 1 and %d\n",
				MAX_PHILOS), 0);
	if (is_number(argv[2]) && ft_atoi(argv[2]) < 60)
		return (printf("Error: Invalid death time\n"), 0);
	if (is_number(argv[3]) && ft_atoi(argv[3]) < 60)
		return (printf("Error: Invalid eating time\n"), 0);
	if (is_number(argv[4]) && ft_atoi(argv[4]) < 60)
		return (printf("Error: Invalid sleeping time\n"), 0);
	if (argc == 6 && (is_number(argv[5]) && ft_atoi(argv[5]) <= 0))
		return (printf("Error: Invalid number of meals\n"), 0);
	return (1);
}
