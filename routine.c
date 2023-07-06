/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:36:20 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/06 17:24:01 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	printf("%lu Philosopher %d is thinking\n", get_time() - philo->data->t_start, philo->name);
	//usleep(1);
	return (0);
}

/* int	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_r);
	printf("%lu Philosopher %d has taken fork %d\n", get_time() - philo->t_start, philo->name, philo->fork_r);

	pthread_mutex_lock(philo->mutex_l);
	printf("%lu Philosopher %d has taken fork %d\n", get_time() - philo->t_start, philo->name, philo->fork_l);	
	return (0);
} */

/* int	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutex_r);
	printf("%lu Philosopher %d has put down fork %d\n", get_time() - philo->t_start, philo->name, philo->fork_r);

	pthread_mutex_unlock(philo->mutex_l);
	printf("%lu Philosopher %d has put down fork %d\n", get_time() - philo->t_start, philo->name, philo->fork_l);	
	return (0);
} */

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks[philo->fork_r]));
	printf("%lu Philosopher %d has taken fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_r);

	pthread_mutex_lock(&(philo->data->forks[philo->fork_l]));
	printf("%lu Philosopher %d has taken fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_l);

	pthread_mutex_lock(&philo->mutex_philo);
	philo->eating = 1;
	philo->t_last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_philo);

	printf("%lu Philosopher %d is eating\n", get_time() - philo->data->t_start, philo->name);
	usleep(philo->data->t_eat * 1000);
	
	pthread_mutex_lock(&philo->mutex_philo);
	philo->eating = 0;
	philo->meals_eaten++;
	if(philo->meals_eaten == philo->data->n_meals)
		philo->finished = 1;
	pthread_mutex_unlock(&philo->mutex_philo);

	pthread_mutex_unlock(&(philo->data->forks[philo->fork_l]));
	printf("%lu Philosopher %d has put down fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_l);

	pthread_mutex_unlock(&(philo->data->forks[philo->fork_r]));
	printf("%lu Philosopher %d has put down fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_r);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	usleep(philo->data->t_sleep * 1000);
	printf("%lu Philosopher %d is sleeping\n", get_time() - philo->data->t_start, philo->name);
	return (0);
}

int	check_super(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->mutex_super);
	if (data->n_dead != 0)
		i = 1;
	pthread_mutex_unlock(&data->mutex_super);
	return (i);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while(philo->finished == 0)
	{
		if (check_super(philo->data) == 1)
			return (0);
		think(philo);
		if (check_super(philo->data) == 1)
			return (0);
		eat(philo);
		if (check_super(philo->data) == 1)
			return (0);
		ft_sleep(philo);
		if (check_super(philo->data) == 1)
			return (0);
	}
	return (0);
}
