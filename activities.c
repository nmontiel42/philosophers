/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:29:33 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/14 14:14:58 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp("died", str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	sleep_philo(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken the right fork", philo);
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->dead_time);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken the left fork", philo);
	pthread_mutex_lock(&philo->lock);
	philo->die_time = get_time() + philo->data->dead_time;
	pthread_mutex_unlock(&philo->lock);
	philo->eating = 1;
	print_message("is eating", philo);
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->times_eat++;
}
