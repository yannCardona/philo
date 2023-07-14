/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:48:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/14 12:48:52 by ycardona         ###   ########.fr       */
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
		data->n_meals = -1;
	sem_unlink("grab_lock");
	data->grab_lock = sem_open("grab_lock", O_CREAT, 0777, 1);
	if (data->grab_lock == NULL)
		return (7);
	sem_unlink("forks_sem");
	data->forks_sem = sem_open("forks_sem", O_CREAT, 0777, data->n_philo);
	if (data->forks_sem == NULL)
		return (5);
	sem_unlink("print_lock");
	data->print_lock = sem_open("print_lock", O_CREAT, 0777, 1);
	if (data->print_lock == NULL)
		return (6);
	data->t_start = get_time();
	return (0);
}

void	init_philo(t_data *data, int i, t_philo *philo)
{
	philo->data = data;
	philo->name = i;
	philo->finished = 0;
	philo->meals_eaten = 0;
	philo->t_last_meal = data->t_start;
	philo->forks_sem = sem_open("forks_sem", 0);
	philo->print_lock = sem_open("print_lock", 0);
	philo->grab_lock = sem_open("grab_lock", 0);
	if (pthread_mutex_init(&philo->mutex_philo, NULL) != 0)
		exit (7);
	if (pthread_create(&philo->supervisor, NULL, &supervising, philo) != 0)
		exit (1);
}
