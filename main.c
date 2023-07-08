/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:43:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/08 12:40:50 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 	ft_exit(t_data *data)
{
	int i;

	pthread_mutex_destroy(&data->mutex_super);
	pthread_mutex_destroy(&data->mutex_write);
	i = 0;
	while(i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex_philo);
		i++;
	}
	free(data->philos);
	free(data->forks);
	free(data);
}

void	*supervising(void *arg)
{
	t_data	*data;
	int	i;

	data = (t_data *) arg;
	while (data)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->philos[i].mutex_philo);
			if (data->t_die < get_time() - data->philos[i].t_last_meal && data->philos[i].eating != 1)
			{
				pthread_mutex_lock(&data->mutex_super);
				data->n_dead++;
				pthread_mutex_unlock(&data->mutex_super);
				ft_print(&data->philos[i], "die");
				pthread_mutex_unlock(&data->philos[i].mutex_philo);
				return (0);
			}
			pthread_mutex_unlock(&data->philos[i].mutex_philo);
			i++;
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
	ft_exit(data);
	return (0);
}
