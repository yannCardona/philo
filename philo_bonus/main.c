/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:43:46 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/12 15:49:33 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_fork(t_data *data, int *pid)
{
	int	i;

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
}

void	ft_wait(t_data *data, int *pid)
{
	int	i;
	int	status;
	
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
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	pid_t		*pid;

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
	ft_fork(data, pid);
	ft_wait(data, pid);
	sem_close(data->forks_sem);
	sem_close(data->print_lock);
	free(data);
	free(pid);
	return (0);
}
