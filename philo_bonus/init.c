/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:48:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/11 11:28:12 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* int	init_mutex(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (5);
		i++;
	}
	if (pthread_mutex_init(&data->mutex_super, NULL) != 0)
			return (6);
	if (pthread_mutex_init(&data->mutex_write, NULL) != 0)
			return (7);
	return (0);
} */

int	init_data(int argc, char *argv[], t_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	else
		data->n_meals = __INT_MAX__;
	data->n_dead = 0;
	data->forks = sem_open("forks", O_CREAT, O_RDWR, data->n_philo);
	if (pthread_mutex_init(&data->mutex_super, NULL) != 0)
			return (6);
	if (pthread_mutex_init(&data->mutex_write, NULL) != 0)
			return (7);
	data->t_start = get_time();
	return (0);
}

t_philo	*init_philo(t_data *data, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->data = data;
	philo->name = i;
	philo->dead = 0;
	philo->finished = 0;
	philo->meals_eaten = 0;
	philo->t_last_meal = get_time();
	philo->forks = data->forks;

	return (philo);
}