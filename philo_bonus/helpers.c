/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:56 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/12 14:05:24 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long int) (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	u_s1 = (unsigned char *) s1;
	u_s2 = (unsigned char *) s2;

	i = 0;
	while ((u_s1[i] || u_s2[i]))
	{
		if (u_s1[i] != u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
	if (u_s1[i] && !u_s2[i])
		return (u_s1[i]);
	if (!u_s1[i] && u_s2[i])
		return (-u_s2[i]);
	return (0);
}

int	check_time(t_philo *philo)
{
	int i;

	i = 0;
	pthread_mutex_lock(&philo->mutex_philo);
	if (philo->data->t_die < get_time() - philo->t_last_meal)
		i = 1;
	pthread_mutex_unlock(&philo->mutex_philo);
	return (i);
}

void	ft_print(t_philo *philo, char *action)
{
	sem_wait(philo->print_lock);
	if (ft_strcmp(action, "die") == 0 && philo->finished != 1)
	{
		printf("%lu %d died\n", get_time() - philo->data->t_start, philo->name);
		return ;
	}
	if (ft_strcmp(action, "fork_r") == 0)
		printf("%lu %d has taken a fork\n", get_time() - philo->data->t_start, philo->name);
	if (ft_strcmp(action, "fork_l") == 0)
		printf("%lu %d has taken a fork\n", get_time() - philo->data->t_start, philo->name);
	if (ft_strcmp(action, "eat") == 0)
		printf("%lu %d is eating\n", get_time() - philo->data->t_start, philo->name);
	if (ft_strcmp(action, "sleep") == 0)
		printf("%lu %d is sleeping\n", get_time() - philo->data->t_start, philo->name);
	if (ft_strcmp(action, "think") == 0)
		printf("%lu %d is thinking\n", get_time() - philo->data->t_start, philo->name);
	sem_post(philo->print_lock);
}
