/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:34:06 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/13 15:31:05 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_philos_finished(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if (!philosopher_finished(&data->philos[i]))
		{
			pthread_mutex_unlock(&data->philos[i].lock);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].lock);
		i++;
	}
	return (1);
}

bool	philosopher_finished(t_philo *philo)
{
	bool	finished;

	pthread_mutex_lock(&philo->lock);
	finished = (philo->times_eat >= philo->data->num_meals);
	pthread_mutex_unlock(&philo->lock);
	return (finished);
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
