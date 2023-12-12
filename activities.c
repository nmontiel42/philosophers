/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:29:33 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/12 15:47:34 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strncmp("died", str, 4) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	think(t_philo *philo)
{
	print_message("is thinkinh", philo, philo->id);
}

void	sleep_philo(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken the right fork", philo, philo->id);
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->dead_time);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken the left fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->lock);
	philo->die_time = get_time() + philo->data->dead_time;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
