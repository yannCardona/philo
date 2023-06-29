/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:36:16 by ycardona          #+#    #+#             */
/*   Updated: 2023/06/28 17:21:17 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>

typedef struct data_s
{

	int	n_philo;
	int	n_meals;
	int	t_eat;
	int	t_sleep;
	int	t_die;
	int	*forks;

} data_t;

typedef struct philo_s
{
	pthread_t t;
	int	status;
	int *fork_r;
	int	*fork_l;
	
} philo_t;

#endif