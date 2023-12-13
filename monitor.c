/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:34:06 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/13 13:05:50 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philosopher_dead(t_philo *philo)
{
	u_int64_t	current_time;
	bool		is_dead;

	pthread_mutex_lock(&philo->lock);
	current_time = get_time();
	is_dead = (current_time >= philo->die_time);
	pthread_mutex_unlock(&philo->lock);
	return (is_dead);
}

bool	philosopher_finished(t_philo *philo)
{
	bool	is_finished;

	pthread_mutex_lock(&philo->lock);
	is_finished = (philo->times_eat >= philo->data->num_meals);
	pthread_mutex_unlock(&philo->lock);
	return (is_finished);
}

/*bool	all_philosophers_finished(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if (!data->finished)
		{
			pthread_mutex_unlock(&data->philos[i].lock);
			return (false);
		}
		pthread_mutex_unlock(&data->philos[i].lock);
		i++;
	}
	return (true);
}*/
