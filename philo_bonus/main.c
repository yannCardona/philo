/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:43:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/10 17:06:37 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


/* void	*supervising(void *arg)
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
} */

int	intput_checker(int argc, char *argv[])
{
	int	i;
	int	j;
	
	if (argc < 5 || 6 < argc)
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

void	routine(t_data *data, int i)
{
	printf("child %d of %d \n", i, data->n_philo);	
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	//pthread_t	supervisor;
	int			i;
	pid_t		pid;
	sem_t		*forks;

	if (intput_checker(argc, argv) != 0)
		return (intput_checker(argc, argv));
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (3);
	if (init_data(argc, argv, data) != 0)
		return (init_data(argc, argv, data));
	forks = sem_open("forks", O_CREAT, O_RDWR, data->n_philo);
	i = 0;
	while (i < data->n_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			routine(data, i + 1);
			exit(0);
		}
		usleep(10);
		i++;
	}
	//ft_exit(data);
	return (0);
}
