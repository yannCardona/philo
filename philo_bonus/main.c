/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:43:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/12 13:53:42 by ycardona         ###   ########.fr       */
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
		usleep(5);
	}	
	return (0);
}

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
	pthread_mutex_lock(&philo->mutex_philo);
	philo->t_last_meal = get_time();
	philo->meals_eaten++;
	if(philo->meals_eaten == philo->data->n_meals)
		philo->finished = 1;
	pthread_mutex_unlock(&philo->mutex_philo);
	ft_print(philo, "eat");
	usleep(philo->data->t_eat * 1000);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
	return (0);
}

void	routine(t_data *data, int i)
{
	pthread_t	supervisor;
	t_philo		*philo;

	philo = init_philo(data, i);
	if (pthread_create(&supervisor, NULL, &supervising, philo) != 0)
		exit (1);
	while (philo->finished == 0)
	{
		ft_print(philo, "think");
		sem_wait(philo->forks_sem);
		ft_print(philo, "fork_r");
		sem_wait(philo->forks_sem);
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
	if (pthread_join(supervisor, NULL) != 0)
		exit (1);
	sem_unlink("forks");
	sem_unlink("print_lock");
	return;
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	int			i;
	pid_t		*pid;
	int 		status;

	if (intput_checker(argc, argv) != 0)
		return (intput_checker(argc, argv));
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (3);
	pid = malloc(sizeof(pid_t) * data->n_philo);
	if (pid == NULL)
		return (4);
	if (init_data(argc, argv, data) != 0)
		return (init_data(argc, argv, data));
	i = 0;
	while (i < data->n_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			routine(data, i + 1);
			exit(0);
		}
		i++;		
		usleep(2);
	}
	i = 0;
	while (i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		if (status == 8448)
		{
			i = 0;
			while (i < data->n_philo)
			{
				kill(pid[i], SIGTERM);
				i++;
			}
		}
		i++;
	}
	sem_close(data->forks_sem);
	sem_close(data->print_lock);
	//printf("I'm still alive - ready to free!!\n");
	//sem_close(forks_lock);
	//ft_exit(data);
	return (0);
}
