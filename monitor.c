/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:34:06 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/14 15:57:31 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *pointer)
{
	t_data	*data;

	data = (t_data *) pointer;
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		if (check_all_philos_finished(data))
		{
			data->dead = 1;
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
	}
	return (pointer);
}

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
