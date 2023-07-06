/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:28:56 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/06 09:29:50 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	/* if (gettimeofday(&tv, NULL))
		return (-11); */
	return ((unsigned long int) (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}
