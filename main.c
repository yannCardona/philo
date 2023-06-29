/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:33:19 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/28 17:16:11 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_read_data(int argc, char *argv[], data_t *data)
{
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
		data->n_meals = -1;
	return (0);
}

int	routine()
{
	return (0);
}

int	main(int argc, char *argv[])
{
	data_t		data;
	pthread_t	*thr;
	int			i;
	
	if (ft_read_data(argc, argv, &data) == 1)
		return (1);
	thr = malloc(sizeof(int) * data.n_philo);
	if (thr == NULL)
		return (1);
	i = 0;
	while(i < data.n_philo)
	{
		if (pthread_create(&thr[i], NULL, &routine, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while(i < data.n_philo)
	{
		if (pthread_join(thr[i], NULL) != 0)
			return (1);
		i++;
	}
}