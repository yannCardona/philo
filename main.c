/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:43:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/06 17:20:28 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 	ft_free(t_data *data)
{
	free(data->philos);
	free(data->forks);
	free(data);
}

void	*supervising(void *arg)
{
	t_data	*data;
	int	i;

	data = (t_data *) arg;
	while (data->n_finished != data->n_meals)
	{
		i = 0;
		data->n_finished = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->philos[i].mutex_philo);
			if (data->t_die < get_time() - data->philos[i].t_last_meal && data->philos[i].eating != 1)
			{
				pthread_mutex_lock(&data->mutex_super);
				data->n_dead++;
				pthread_mutex_unlock(&data->mutex_super);
				printf("%lu Philosopher %d has died \n", get_time() - data->t_start, data->philos[i].name);
				pthread_mutex_unlock(&data->philos[i].mutex_philo);
				return (0);
			}
			pthread_mutex_unlock(&data->philos[i].mutex_philo);
			pthread_mutex_lock(&data->philos[i].mutex_philo);
			if (data->philos[i].finished == 1)
				data->n_finished++;
			pthread_mutex_unlock(&data->philos[i].mutex_philo);
			i++;
		}
		if (data->n_finished == data->n_meals)
		{
			pthread_mutex_lock(&data->mutex_super);
			data->n_dead++;
			pthread_mutex_unlock(&data->mutex_super);
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	pthread_t	supervisor;
	int			i;

	if (argc < 5 || 6 < argc)
		return (1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (2);
	if (init_data(argc, argv, data) != 0)
		return (3);
	i = 0;
	while(i < data->n_philo)
	{
		if (init_philo(&data->philos[i], i, data) != 0)
			return (4);
		i++;
	}
	if (pthread_create(&supervisor, NULL, &supervising, (void *) data) != 0)
		return (5);
	
	i = 0;
	while(i < data->n_philo)
	{
		if (pthread_join(data->philos[i].thr, NULL) != 0)
			return (6);
		i++;
	}
	if (pthread_join(supervisor, NULL) != 0)
		return (7);
	return (0);
}
