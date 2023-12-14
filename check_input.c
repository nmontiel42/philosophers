/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:53:35 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/14 16:17:30 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	validate_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_printf("Error: Invalid number of arguments\n"), 0);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_PHILOS)
		return (ft_printf("Error: Num of philos must be between 1 and %d\n",
				MAX_PHILOS), 0);
	if (is_number(argv[2]) || ft_atoi(argv[2]) < 60)
		return (ft_printf("Error: Invalid death time\n"), 0);
	if (is_number(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (ft_printf("Error: Invalid eating time\n"), 0);
	if (is_number(argv[4]) || ft_atoi(argv[4]) < 60)
		return (ft_printf("Error: Invalid sleeping time\n"), 0);
	if (argc == 6 && (is_number(argv[5]) || ft_atoi(argv[5]) <= 0))
		return (ft_printf("Error: Invalid number of meals\n"), 0);
	return (1);
}
