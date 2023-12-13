/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:09:11 by nmontiel          #+#    #+#             */
/*   Updated: 2023/12/13 15:34:27 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		supervisor;
	int				id;
	int				times_eat;
	int				status;
	int				eating;
	u_int64_t		die_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				num_philos;
	int				num_meals;
	int				dead;
	int				finished;
	t_philo			*philos;
	u_int64_t		dead_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}				t_data;

//activities.c
void		print_message(char *str, t_philo *philo);
int			ft_strcmp(char *s1, char *s2);
void		think(t_philo *philo);
void		sleep_philo(t_philo *philo);
void		eat(t_philo *philo);

//check_input.c
int			is_number(char *str);
int			validate_input(int argc, char **argv);

//initialize.c
int			allocate_mem(t_data *data);
int			initialize_forks(t_data *data);
void		initialize_philos(t_data *data);
int			initialize_data(t_data *data, char **argv, int argc);
int			initialize(t_data *data, char **argv, int argc);

//main.c
void		*supervisor(void *philo_pointer);
void		*philo_routine(void *arg);
void		*monitor(void *pointer);
int			main(int argc, char **argv);
int			initialize_threads(t_data *data);

//monitor.c
int			check_all_philos_finished(t_data *data);
bool		philosopher_finished(t_philo *philo);
//bool		all_philosophers_finished(t_data *data);

//utils_philo.c
int			ft_error(char *str, t_data *data);
void		ft_destroy(t_data *data);
void		ft_free(t_data *data);
u_int64_t	get_time(void);
int			ft_usleep(useconds_t time);


#endif