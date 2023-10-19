/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:37:00 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:07:07 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

uint64_t	timedif(int i)
{
	uint64_t	time;

	pthread_mutex_lock(&data()->philos[i].action_lock);
	time = now() - data()->philos[i].action_start + data()->time_to_die;
	pthread_mutex_unlock(&data()->philos[i].action_lock);
	return (time);
}

int	ready_start(t_philo *philos)
{
	while (TRUE)
	{
		pthread_mutex_lock(&data()->start_lock);
		if (data()->start_flag == ERROR)
		{
			pthread_mutex_unlock(&data()->start_lock);
			return (ERROR);
		}
		if (data()->start_flag == TRUE)
			break ;
		pthread_mutex_unlock(&data()->start_lock);
	}
	pthread_mutex_unlock(&data()->start_lock);
	if (philos->id % 2 == 0)
		usleep(20);
	return (FINISH);
}

uint64_t	now(void)
{
	struct timeval	tv;
	uint64_t		current;

	gettimeofday(&tv, NULL);
	current = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000);
	return (current);
}

void	set_start_time(t_param *params)
{
	uint64_t	time;
	int			i;

	i = 0;
	time = now();
	while (i < params->u_param.param[0])
		data()->philos[i++].start_time = time;
}

void	ft_usleep(int sleep)
{
	const uint64_t	current = now();

	usleep((sleep) * 900);
	while (TRUE)
	{
		if (now() - current >= ((uint64_t)sleep))
			break ;
	}
}
