/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:43:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/12 16:13:18 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void 	ft_exit(t_data *data)
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
			if (data->t_die < get_time() - data->philos[i].t_last_meal)
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
		usleep(2);
	}
	return (0);
}

int	intput_checker(int argc, char *argv[])
{
	int	i;
	int	j;
	
	if (argc < 5 || 6 < argc)
		return (1);
	if (ft_atoi(argv[1]) == 0)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (2);
			j++;
		}
		i++;
	}
	return (0);
}

int	create_threads(t_data *data, pthread_t *supervisor)
{
	int i;
	
	i = 0;
	while(i < data->n_philo)
	{
		if (init_philo(&data->philos[i], i, data) != 0)
			return (11);
		i++;
	}
	if (pthread_create(supervisor, NULL, &supervising, (void *) data) != 0)
		return (12);
	return (0);
}

int	join_threads(t_data *data, pthread_t supervisor)
{
	int	i;
	
	i = 0;
	while(i < data->n_philo)
	{
		if (pthread_join(data->philos[i].thr, NULL) != 0)
			return (13);
		i++;
	}
	if (pthread_join(supervisor, NULL) != 0)
		return (14);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	pthread_t	supervisor;

	if (intput_checker(argc, argv) != 0)
		return (intput_checker(argc, argv));
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (3);
	if (init_data(argc, argv, data) != 0)
		return (init_data(argc, argv, data));
	if (create_threads(data, &supervisor) != 0)
		return (create_threads(data, &supervisor));
	if (join_threads(data, supervisor) != 0)
		return (join_threads(data, supervisor));
	ft_exit(data);
	return (0);
}
