/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:05:28 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/12 16:32:43 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philosopher_dead(philo))
		{
			print_message("died", philo, philo->id);
			break ;
		}
		if (philosopher_finished(philo))
			break ;
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

void	*monitor(void *pointer)
{
	t_data	*data;

	data = (t_data *)pointer;
	while (1)
	{
		if (all_philosophers_finished(data))
		{
			pthread_mutex_lock(&data->lock);
			data->finished = 1;
			pthread_mutex_unlock(&data->lock);
			break ;
		}
	}
	return (pointer);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	pthread_t	philo_threads[MAX_PHILOS];
	int			i;

	if (!validate_input(argc, argv))
		return (1);
	if (initialize(&data, argv, argc))
		return (1);
	if (data.num_meals != -1)
	{
		pthread_create(&monitor_thread, NULL, monitor, (void *)&data);
		pthread_detach(monitor_thread);
	}
	i = 0;
	while (i < data.num_philos)
	{
		pthread_create(&philo_threads[i], NULL, philo_routine,
			(void *)&data.philos[i]);
		i++;
	}
	if (data.num_meals != -1)
		pthread_cancel(monitor_thread);
	destroy_resources(&data);
	return (0);
}

void	destroy_resources(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	if (data->num_meals != -1)
		pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free(data->philos);
}
