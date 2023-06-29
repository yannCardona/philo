/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:36:16 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/29 16:35:27 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct philo_s
{
	pthread_t t;
	int	name;
	int	status;
	int fork_r;
	int	fork_l;
	int	meals_eaten;
	
} philo_t;

typedef struct data_s
{
	pthread_t		*thr;
	pthread_mutex_t	mutex_r;
	pthread_mutex_t	mutex_l;
	pthread_mutex_t	mutex_init;
	//philo_t			philo;

	int				*forks;
	int				n_philo;
	int				n_meals;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	//int				current;

} data_t;

#endif