/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:02:46 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:01:58 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	alldone(void)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (TRUE)
	{
		pthread_mutex_lock(&data()->philos[i].meal_lock);
		if (data()->philos[i].nb_to_eat == 0)
			count++;
		else
		{
			pthread_mutex_unlock(&data()->philos[i].meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data()->philos[i].meal_lock);
		if (count == data()->nb_philos)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

bool	murder_philo(t_philo *philos)
{
	pthread_mutex_lock(&data()->dead_lock);
	if (data()->dead_flag == FALSE)
	{
		data()->dead_flag = TRUE;
		pthread_mutex_unlock(&data()->dead_lock);
		print_action(philos, DIED);
		return (TRUE);
	}
	pthread_mutex_unlock(&data()->dead_lock);
	return (FALSE);
}

static bool	guillotine(int i)
{
	while (TRUE)
	{
		pthread_mutex_lock(&data()->philos[i].action_lock);
		if (data()->philos[i].action != EAT)
			break ;
		pthread_mutex_unlock(&data()->philos[i].action_lock);
	}
	pthread_mutex_unlock(&data()->philos[i].action_lock);
	ft_usleep(timedif(i));
	return (murder_philo(&data()->philos[i]));
}

static bool	scythe(int i)
{
	while (TRUE)
	{
		pthread_mutex_lock(&data()->philos[i].action_lock);
		if (data()->philos[i].action_start
			+ data()->time_to_die <= data()->time_to_eat
			+ data()->philos[i].action_start && data()->philos[i].action != EAT)
			break ;
		if (data()->philos[i].action_start
			+ data()->time_to_die <= data()->time_to_eat + data()->time_to_sleep
			+ data()->philos[i].action_start && data()->philos[i].action != EAT)
			break ;
		if (data()->time_to_eat > data()->time_to_sleep)
		{
			if (data()->philos[i].action_start
				+ data()->time_to_die <= (data()->time_to_eat * 2)
				+ data()->philos[i].action_start)
				break ;
		}
		pthread_mutex_unlock(&data()->philos[i].action_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&data()->philos[i].action_lock);
	return (DEAD);
}

void	*the_reaper(void)
{
	int	i;

	i = 0;
	while (TRUE)
	{
		pthread_mutex_lock(&data()->start_lock);
		if (data()->start_flag == TRUE)
			break ;
		pthread_mutex_unlock(&data()->start_lock);
	}
	pthread_mutex_unlock(&data()->start_lock);
	while (TRUE)
	{
		if (scythe(i))
		{
			(guillotine(i));
			return (NULL);
		}
		if (data()->to_eat != INVALID)
			if (alldone())
				return (NULL);
		if (++i == data()->nb_philos)
			i = 0;
	}
	return (NULL);
}
