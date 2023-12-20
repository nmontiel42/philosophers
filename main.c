/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:05:28 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/20 11:51:48 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *philo_pointer)
{
	t_philo		*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->die_time && philo->eating == 0)
		{
			print_message("died", philo);
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->lock);
		if (philo->data->num_meals > 0 && philo->times_eat
			>= philo->data->num_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		ft_usleep(1);
	}
	return ((void *) 0);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	int			has_eaten_enough;

	philo = (t_philo *)arg;
	philo->die_time = philo->data->dead_time + get_time();
	if (pthread_create(&philo->supervisor, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		print_message("is thinking", philo);
		sleep_philo(philo);
		if (philo->data->num_meals > 0 && philo->times_eat
			>= philo->data->num_meals)
			break ;
	}
	if (pthread_join(philo->supervisor, NULL))
		return ((void *)1);
	return ((void *) 0);
}
/*void	ft_leaks(void)
{
	system("leaks -q philo");
}*/

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
