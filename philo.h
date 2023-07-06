/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:33:15 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/06 16:38:18 by ycardona         ###   ########.fr       */
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
	pthread_t		thr;
	pthread_mutex_t	mutex_philo;

	int	name;
	int eating;
	int	finished;
	int	meals_eaten;
	int fork_r;
	int	fork_l;
	unsigned long int	t_last_meal;
} t_philo;

typedef struct s_data
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_super;

	int					n_philo;
	int					n_meals;
	int					n_dead;
	int					n_finished;
	unsigned long int	t_eat;
	unsigned long int	t_sleep;
	unsigned long int	t_die;
	unsigned long int	t_start;

} t_data;

unsigned long int	get_time(void);
int					init_data(int argc, char *argv[], t_data *data);
int					init_philo(t_philo *philo, int i, t_data *data);
void				*routine(void *arg);

#endif