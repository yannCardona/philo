/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:33:19 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/01 17:24:28 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	/* if (gettimeofday(&tv, NULL))
		return (-11); */
	return ((u_int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	*monitor_a(void *arg)
{
	data_t		*data;
	
	data = (data_t *) arg;

	while(data->n_dead == 0)
	{
		pthread_mutex_lock(data->mutex_data);
		if (data->n_finished == data->n_philo)
			data->n_dead++;
		pthread_mutex_unlock(data->mutex_data);
	}
	return (0);
}

void	*monitor_p(void *arg)
{
	philo_t		*philo;
	
	philo = (philo_t *) arg;
	
	while (philo->data->n_dead == 0 && 	philo->finished == 0)
	{
		pthread_mutex_lock(&philo->mutex_philo);
		if (philo->t_dead <= get_time() && philo->eating == 0)
		{
			pthread_mutex_lock(philo->data->mutex_data);
			philo->data->n_dead++;
			pthread_mutex_unlock(philo->data->mutex_data);
			printf("%llu Philosopher %d died\n", get_time() - philo->data->t_start, philo->name);
		}
		if (philo->meals_eaten == philo->data->n_meals)
		{
			philo->finished = 1;
			pthread_mutex_lock(philo->data->mutex_data);
			philo->data->n_finished++;
			pthread_mutex_unlock(philo->data->mutex_data);
			printf("%llu Philosopher %d has finished\n", get_time() - philo->data->t_start, philo->name);
		}
		pthread_mutex_unlock(&philo->mutex_philo);
	}
	return (0);
}

void	*routine(void *arg)
{
	philo_t		*philo;
	pthread_t	monitor_philo;
	
	philo = (philo_t *) arg;

	if (pthread_create(&monitor_philo, NULL, &monitor_p, (void *) philo) != 0)
			return (NULL);
			
	while (philo->data->n_dead == 0 && philo->meals_eaten < philo->data->n_meals)
	{
		printf("%llu Philosopher %d is thinking\n", get_time() - philo->data->t_start, philo->name);
		
		pthread_mutex_lock(philo->mutex_r);
		printf("%llu Philosopher %d has taken fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_r);
		
		pthread_mutex_lock(philo->mutex_l);
		printf("%llu Philosopher %d has taken fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_l);
		
		pthread_mutex_lock(&philo->mutex_philo);
		philo->eating = 1;
		printf("%llu Philosopher %d is eating\n", get_time() - philo->data->t_start, philo->name);
		usleep(philo->data->t_eat * 1000);
		philo->eating = 0;
		philo->meals_eaten++;
		philo->t_dead = get_time() + philo->data->t_die;
		pthread_mutex_unlock(&philo->mutex_philo);

		pthread_mutex_unlock(philo->mutex_l);
		printf("%llu Philosopher %d has put down fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_l);
		pthread_mutex_unlock(philo->mutex_r);
		printf("%llu Philosopher %d has put down fork %d\n", get_time() - philo->data->t_start, philo->name, philo->fork_r);

		usleep(philo->data->t_sleep * 1000);
		printf("%llu Philosopher %d is sleeping\n", get_time() - philo->data->t_start, philo->name);
	}
	if (pthread_join(monitor_philo, NULL) != 0)
			return (NULL);
	return (0);
}

int	ft_init_data(int argc, char *argv[], data_t *data)
{
	int	i;
	if (argc < 5 || 6 < argc)
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	//check the atois
	data->n_philo = atoi(argv[1]);
	data->n_dead = 0;
	data->n_finished = 0;
	data->t_die = atoi(argv[2]);
	data->t_eat = atoi(argv[3]);
	data->t_sleep = atoi(argv[4]);
	if (argc == 6)
		data->n_meals = atoi(argv[5]);
	else
		data->n_meals = __INT_MAX__;
	
	i = 0;
	pthread_mutex_init(data->mutex_data, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while (i < data->n_philo)
	{
		data->forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	data->philo = malloc(sizeof(philo_t *) * data->n_philo);
	if (data->philo == NULL)
		return (1);
	data->t_start = get_time();
	return (0);
}

philo_t	*philo_init(data_t *data, int i)
{
	philo_t	*philo;
	
	philo = malloc(sizeof(philo_t));
	if (philo == NULL)
		return (NULL);
	philo->data = data;
	philo->name = i + 1;
	philo->eating = 0;
	philo->meals_eaten = 0;
	philo->finished = 0;
	philo->t_dead = get_time() + data->t_die;
	philo->fork_r = i;
	if (i == data->n_philo - 1)
		philo->fork_l = 0;
	else 
		philo->fork_l = i + 1;
	philo->mutex_r = philo->data->forks[philo->fork_r];
	philo->mutex_l = philo->data->forks[philo->fork_l];
	pthread_mutex_init(&philo->mutex_philo, NULL);
	if (pthread_create(&philo->thr, NULL, &routine, (void *) philo) != 0)
			return (NULL);
	return (philo);
}

int	main(int argc, char *argv[])
{
	data_t		data;
	pthread_t	monitor_all;
	int			i;

	if (ft_init_data(argc, argv, &data) == 1)
		return (1);
	if (pthread_create(&monitor_all, NULL, &monitor_a, (void *) &data) != 0)
		return (1);
	i = 0;
	while(i < data.n_philo)
	{
		data.philo[i] = philo_init(&data, i);
		if (data.philo[i] == NULL)
			return (1);
		usleep(1);
		i++;
	}
	i = 0;
	while(i < data.n_philo)
	{
		if (pthread_join(data.philo[i]->thr, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(monitor_all, NULL) != 0)
		return (1);
	//pthread_mutex_destroy(&data.mutex_r);
	//pthread_mutex_destroy(&data.mutex_l);
	return (0);
}
