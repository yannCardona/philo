/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:48:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/12 13:40:39 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_unlink("forks_sem");
	data->forks_sem = sem_open("forks_sem", O_CREAT, 0660, data->n_philo);
	sem_unlink("print_lock");
	data->print_lock = sem_open("print_lock", O_CREAT, 0660, 1);
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
	philo->finished = 0;
	philo->meals_eaten = 0;
	philo->t_last_meal = get_time();
	if (pthread_mutex_init(&philo->mutex_philo, NULL) != 0)
			exit (7);
	philo->forks_sem = sem_open("forks_sem", 0);
	philo->print_lock = sem_open("print_lock", 0);
	return (philo);
}
