/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:47:31 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/14 16:17:23 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_mem(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->tid)
		return (ft_error("Error malloc 1", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (ft_error("Error malloc 2", data));
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (ft_error("Error malloc 3", data));
	return (0);
}

int	initialize_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->num_philos - 1];
	i = 1;
	while (i < data->num_philos)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	initialize_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].die_time = data->dead_time;
		data->philos[i].times_eat = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	initialize_data(t_data *data, char **argv, int argc)
{
	data->num_philos = ft_atoi(argv[1]);
	data->dead_time = (u_int64_t)ft_atoi(argv[2]);
	data->eat_time = (u_int64_t)ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t)ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	if (data->num_philos <= 0 || data->num_philos > MAX_PHILOS
		|| data->dead_time < 0 || data->eat_time < 0 || data->sleep_time < 0)
		return (ft_error("Error data", NULL));
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	initialize(t_data *data, char **argv, int argc)
{
	if (initialize_data(data, argv, argc))
		return (1);
	if (allocate_mem(data))
		return (1);
	if (initialize_forks(data))
		return (1);
	initialize_philos(data);
	return (0);
}
