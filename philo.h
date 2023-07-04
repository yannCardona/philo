/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:36:16 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/04 12:55:54 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

struct s_data;

typedef struct s_philo
{	
	struct s_data	*data;
	pthread_t	thr;
	//pthread_t	monitor_philo;

	int	name;
	int	alive;
	int eating;
	int	finished;
	int	meals_eaten;
	int fork_r;
	int	fork_l;
	unsigned long int	t_dead;
	
	pthread_mutex_t	*mutex_r;
	pthread_mutex_t	*mutex_l;
	pthread_mutex_t	mutex_philo;
} philo_t;

typedef struct s_data
{
	philo_t				**philo;
	pthread_mutex_t		**forks;
	pthread_mutex_t		mutex_data;
	
	int					n_philo;
	int					n_meals;
	int					n_dead;
	int					n_finished;
	unsigned long int			t_eat;
	unsigned long int			t_sleep;
	unsigned long int			t_die;
	unsigned long int			t_start;

} data_t;

#endif