/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:48:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/06 17:13:23 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int argc, char *argv[], t_data *data)
{
	int		i;

	data->n_philo = atoi(argv[1]);
	data->t_die = atoi(argv[2]);
	data->t_eat = atoi(argv[3]);
	data->t_sleep = atoi(argv[4]);
	if (argc == 6)
		data->n_meals = atoi(argv[5]);
	else
		data->n_meals = __INT_MAX__;
	data->n_dead = 0;
	data->n_finished = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (data->forks == NULL)
		return (11);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (12);
		i++;
	}
	if (pthread_mutex_init(&data->mutex_super, NULL) != 0)
			return (13);
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (data->philos == NULL)
		return (14);
	data->t_start = get_time();
	return (0);
}

int	init_philo(t_philo *philo, int i, t_data *data)
{
	philo->data = data;
	philo->name = i + 1;
	philo->eating = 0;
	philo->finished = 0;
	philo->meals_eaten = 0;
	philo->fork_r = i;
	if (i == data->n_philo - 1)
		philo->fork_l = 0;
	else 
		philo->fork_l = i + 1;
	philo->t_last_meal = get_time();
	if (pthread_mutex_init(&philo->mutex_philo, NULL) != 0)
			return (15);
	if (pthread_create(&philo->thr, NULL, &routine, (void *) philo) != 0)
		return (16);
	return (0);
}