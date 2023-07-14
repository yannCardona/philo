/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:58:36 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/14 02:17:26 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*supervising(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (check_time(philo) == 1)
		{
			ft_print(philo, "die");
			exit (33);
		}
		usleep(1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_philo);
	philo->t_last_meal = get_time();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->n_meals)
		philo->finished = 1;
	pthread_mutex_unlock(&philo->mutex_philo);
	ft_print(philo, "eat");
	usleep(philo->data->t_eat * 1000);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
	return (0);
}

static void	ft_exit(t_philo *philo)
{
	sem_unlink("forks_sem");
	sem_unlink("print_lock");
	pthread_mutex_destroy(&philo->mutex_philo);
	//free(philo);
	exit(0);
}

void	routine(t_data *data, int i)
{
	t_philo	philo;

	init_philo(data, i, &philo);
	while (1)
	{
		ft_print(&philo, "think");
		sem_wait(philo.forks_sem);
		ft_print(&philo, "fork_r");
		sem_wait(philo.forks_sem);
		ft_print(&philo, "fork_l");
		eat(&philo);
		if (philo.finished == 1)
			ft_exit(&philo);
		ft_print(&philo, "sleep");
		usleep(data->t_sleep * 1000);
	}
	if (pthread_join(philo.supervisor, NULL) != 0)
		exit (1);
	ft_exit(&philo);
	return ;
}
