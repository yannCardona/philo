/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:33:19 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/29 16:37:51 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_read_data(int argc, char *argv[], data_t *data)
{
	int	i;
	if (argc < 5 || 6 < argc)
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	//check the atois
	data->n_philo = atoi(argv[1]);
	data->t_die = atoi(argv[2]);
	data->t_eat = atoi(argv[3]);
	data->t_sleep = atoi(argv[4]);
	if (argc == 6)
		data->n_meals = atoi(argv[5]);
	else
		data->n_meals = __INT_MAX__;
	data->forks = malloc(sizeof(int) * data->n_philo);
	if (data->forks == NULL)
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		data->forks[i] = i;
		i++;
	}
	data->thr = malloc(sizeof(int) * data->n_philo);
	if (data->thr == NULL)
		return (1);
	return (0);
}

void	philo_init(data_t *data, philo_t *philo)
{
	int name;

	name = 0;
	while (data->thr[name])
		name++;
	name--;
	philo->t = data->thr[name];
	philo->name = name + 1;
	philo->fork_r = name;
	if (name == data->n_philo - 1)
		philo->fork_l = 0;
	else 
		philo->fork_l = name + 1;
	philo->status = 1;
	philo->meals_eaten = 0;
}

void	*routine(void *arg)
{
	philo_t	philo;
	data_t *data = (data_t *) arg;
	pthread_mutex_lock(&data->mutex_init);
	philo_init(data, &philo);
	pthread_mutex_unlock(&data->mutex_init);

	while (philo.meals_eaten < data->n_meals && philo.status == 1)
	{
		pthread_mutex_lock(&data->mutex_r);
		data->forks[philo.fork_r] = data->forks[philo.fork_r];
		printf("Philosopher %d has taken his right fork\n", philo.name);
		pthread_mutex_lock(&data->mutex_l);
		data->forks[philo.fork_l] = data->forks[philo.fork_l];
		printf("Philosopher %d has taken his left fork\n", philo.name);
		printf("Philosopher %d is eating\n", philo.name);
		usleep(data->t_eat * 1000);
		philo.meals_eaten++;
		pthread_mutex_unlock(&data->mutex_r);
		pthread_mutex_unlock(&data->mutex_l);
				philo.meals_eaten++;

		printf("Philosopher %d is sleeping\n", philo.name);
		usleep(data->t_sleep * 1000);
		printf("Philosopher %d is thinking\n", philo.name);
	}
	
	return (0);
}

int	main(int argc, char *argv[])
{
	data_t		data;
	int			i;
	
	if (ft_read_data(argc, argv, &data) == 1)
		return (1);
	pthread_mutex_init(&data.mutex_r, NULL);
	pthread_mutex_init(&data.mutex_l, NULL);
	pthread_mutex_init(&data.mutex_init, NULL);
	i = 0;
	while(i < data.n_philo)
	{
		//data.current = i;
		if (pthread_create(&data.thr[i], NULL, &routine, &data) != 0)
			return (1);
		i++;
	}
	i = 0;
	while(i < data.n_philo)
	{
		if (pthread_join(data.thr[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_destroy(&data.mutex_r);
	pthread_mutex_destroy(&data.mutex_l);
		pthread_mutex_destroy(&data.mutex_init);

	return (0);
}