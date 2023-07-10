/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:36:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/10 09:47:54 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks[philo->fork_r]));
	ft_print(philo, "fork_r");
	pthread_mutex_lock(&(philo->data->forks[philo->fork_l]));
	ft_print(philo, "fork_l");
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_philo);
	philo->t_last_meal = get_time();
	philo->meals_eaten++;
	if(philo->meals_eaten == philo->data->n_meals)
		philo->finished = 1;
	pthread_mutex_unlock(&philo->mutex_philo);
	ft_print(philo, "eat");
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_l]));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_r]));
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while(check_super(philo->data) == 0 && philo->finished == 0)
	{
		ft_print(philo, "think");
		pick_forks(philo);
		eat(philo);
		if (philo->finished == 1)
			return (0);
		usleep(philo->data->t_sleep * 1000);
		ft_print(philo, "sleep");
	}
	return (0);
}
