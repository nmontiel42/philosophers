/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:02:17 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/19 11:30:32 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data, pthread_t *monitor_thread)
{
	int	i;

	data->start_time = get_time();
	if (data->num_meals > 0)
	{
		if (pthread_create(monitor_thread, NULL, &monitor, &data->philos[0]))
			return (printf("Error creating monitor thread"));
	}
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->tid[i], NULL, &philo_routine,
				&data->philos[i]))
			return (printf("Error creating thread"));
		ft_usleep(1);
	}
	return (0);
}

int	wait_for_threads(t_data *data, pthread_t monitor_thread)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(data->tid[i], NULL))
			return (printf("Error waiting for thread"));
	}
	if (data->num_meals > 0)
	{
		if (pthread_join(monitor_thread, NULL))
			return (printf("Error al cancelar el monitor"));
	}
	return (0);
}

int	initialize_threads(t_data *data)
{
	pthread_t	monitor_thread;

	if (create_threads(data, &monitor_thread) != 0)
		return (1);
	if (wait_for_threads(data, monitor_thread) != 0)
		return (1);
	return (0);
}
