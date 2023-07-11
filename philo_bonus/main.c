/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:43:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/11 12:46:26 by ycardona         ###   ########.fr       */
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

int	eat(t_philo *philo)
{
	philo->t_last_meal = get_time();
	philo->meals_eaten++;
	if(philo->meals_eaten == philo->data->n_meals)
		philo->finished = 1;
	ft_print(philo, "eat");
	usleep(philo->data->t_eat * 1000);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (0);
}

void	routine(t_data *data, int i)
{
	//pthread_t	supervisor;
	t_philo		*philo;

	philo = init_philo(data, i);
	while (philo->dead == 0 && philo->finished == 0)
	{
		ft_print(philo, "think");
		sem_wait(philo->forks);
		sem_wait(philo->forks);
		ft_print(philo, "fork_r");
		ft_print(philo, "fork_l");
		eat(philo);
		if (philo->finished == 1)
		{
			sem_unlink("forks");
			exit (0);
		}
		ft_print(philo, "sleep");
		usleep(data->t_sleep * 1000);
	}
	sem_unlink("forks");
	return;
}

int	main(int argc, char *argv[])
{
	t_data		*data;
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
		//usleep(10);
		i++;
	}
	wait (&pid);
	sem_close(data->forks);
	//ft_exit(data);
	return (0);
}
