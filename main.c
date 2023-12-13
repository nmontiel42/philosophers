/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:05:28 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/13 15:34:49 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *philo_pointer)
{
	t_philo		*philo;
	u_int64_t	current_time;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		current_time = get_time();
		if ((current_time - philo->data->start_time) >= philo->data->dead_time)
		{
			print_message("died", philo);
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		if (philo->times_eat == philo->data->num_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(1);
	}
	return ((void *) 0);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (pthread_create(&philo->supervisor, NULL, &supervisor, philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	if (pthread_join(philo->supervisor, NULL))
		return ((void *)1);
	return ((void *) 0);
}

void	*monitor(void *pointer)
{
	t_data	*data;

	data = (t_data *)pointer;
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
	if (initialize_threads(&data))
		return (1);
	ft_destroy(&data);
	return (0);
}

int	initialize_threads(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	data->start_time = get_time();
	if (data->num_meals > 0)
	{
		if (pthread_create(&monitor_thread, NULL, &monitor, &data->philos[0]))
			return (ft_printf("Error creando el hilo monitor"));
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->tid[i], NULL,
				&philo_routine, &data->philos[i]))
			return (ft_printf("Error crando el hilo"));
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->tid[i], NULL))
			return (ft_printf("Error al esperar al hilo"));
		i++;
	}
	if (data->num_meals > 0)
	{
		if (pthread_cancel(monitor_thread))
			return (ft_printf("Error al cancelar el monitor"));
	}
	return (0);
}
