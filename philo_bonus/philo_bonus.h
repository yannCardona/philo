/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:33:15 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/12 14:19:43 by ycardona         ###   ########.fr       */
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
# include <sys/wait.h>
# include <signal.h>

struct s_data;

typedef struct s_philo
{	
	struct s_data	*data;
	pthread_t		supervisor;
	pthread_mutex_t	mutex_philo;
	sem_t			*forks_sem;
	sem_t			*print_lock;

	int	name;
	int	finished;
	int	dead;
	int	meals_eaten;
	unsigned long int	t_last_meal;
} t_philo;

typedef struct s_data
{
	sem_t				*forks_sem;
	sem_t				*print_lock;

	int					n_philo;
	int					n_meals;
	unsigned long int	t_eat;
	unsigned long int	t_sleep;
	unsigned long int	t_die;
	unsigned long int	t_start;

} t_data;

unsigned long int	get_time(void);
int					init_data(int argc, char *argv[], t_data *data);
t_philo				*init_philo(t_data *data, int i);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_print(t_philo *philo, char *action);
int					check_time(t_philo *philo);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
void				routine(t_data *data, int i);
void				*supervising(void *arg);

#endif