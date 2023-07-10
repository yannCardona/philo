/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:33:15 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/10 16:59:03 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

struct s_data;

typedef struct s_philo
{	
	struct s_data	*data;
	pthread_t		thr;
	pthread_mutex_t	mutex_philo;

	int	name;
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
	pthread_mutex_t		mutex_write;

	int					n_philo;
	int					n_meals;
	int					n_dead;
	unsigned long int	t_eat;
	unsigned long int	t_sleep;
	unsigned long int	t_die;
	unsigned long int	t_start;

} t_data;

unsigned long int	get_time(void);
int					init_data(int argc, char *argv[], t_data *data);
int					init_philo(t_philo *philo, int i, t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_print(t_philo *philo, char *action);
int					check_super(t_data *data);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);

#endif