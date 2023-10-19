/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:52:46 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:06:33 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	is_dead(void)
{
	pthread_mutex_lock(&data()->dead_lock);
	if (data()->dead_flag == TRUE)
	{
		pthread_mutex_unlock(&data()->dead_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&data()->dead_lock);
	return (FALSE);
}

static void	go_sleep(t_philo *philos)
{
	if (!is_dead())
	{
		pthread_mutex_lock(&philos->action_lock);
		philos->action = SLEEP;
		pthread_mutex_unlock(&philos->action_lock);
		print_action(philos, SLEEP);
		ft_usleep(data()->time_to_sleep);
		pthread_mutex_lock(&philos->action_lock);
		philos->action = WAIT_TO_EAT;
		pthread_mutex_unlock(&philos->action_lock);
	}
}

static bool	still_eating(t_philo *philos)
{
	pthread_mutex_lock(&philos->meal_lock);
	if (philos->nb_to_eat > 0)
		philos->nb_to_eat--;
	if (philos->nb_to_eat == 0)
	{
		pthread_mutex_unlock(&philos->meal_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&philos->meal_lock);
	return (TRUE);
}

static void	eat(t_philo *philos)
{
	if (!is_dead())
	{
		print_mutex(philos, TRUE);
		pthread_mutex_lock(&philos->action_lock);
		philos->action = EAT;
		philos->action_start = now();
		pthread_mutex_unlock(&philos->action_lock);
		print_action(philos, EAT);
		ft_usleep(data()->time_to_eat);
		pthread_mutex_lock(&philos->action_lock);
		philos->action = WAIT_TO_SLEEP;
		pthread_mutex_unlock(&philos->action_lock);
		print_mutex(philos, FALSE);
	}
}

// static int	eat(t_philo *philos)
// {
// 	if (!is_dead())
// 		make_eat(philos);
// 	return (DONE);
// }

void	*routine(void *info)
{
	t_philo	*philos;

	philos = (t_philo *)info;
	if (ready_start(philos) == ERROR)
		return (NULL);
	pthread_mutex_lock(&philos->meal_lock);
	if (!philos->nb_to_eat)
		return (NULL);
	pthread_mutex_unlock(&philos->meal_lock);
	while (!is_dead())
	{
		print_action(philos, THINK);
		if (!is_dead())
			eat(philos);
		if (!still_eating(philos))
			return (NULL);
		go_sleep(philos);
	}
	return (NULL);
}
