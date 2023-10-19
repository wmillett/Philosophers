/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:48:51 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:00:02 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	printt(uint64_t start)
{
	uint64_t	time;
	uint64_t	current;

	current = now();
	time = current - start;
	printf("%llums ", time);
}

int	printm(int philo, int action, uint64_t start)
{
	uint64_t	time;

	time = now() - start;
	if (action == EAT)
		printf("%llums Philosopher[%i] is eating 🍚\n", time, philo);
	if (action == SLEEP)
		printf("%llums Philosopher[%i] is sleeping 😴\n", time, philo);
	if (action == THINK)
		printf("%llums Philosopher[%i] is thinking 🤔\n", time, philo);
	if (action == TAKE)
		printf("%llums Philosopher[%i] has taken a fork 🥢\n", time, philo);
	if (action == DIED)
		printf("%llums Philosopher[%i] died 💀\n", time, philo);
	if (action == TEST)
		printf("%llums test at this thread: %i", time, philo);
	return (TRUE);
}

void	print_action(t_philo *philos, int action)
{
	pthread_mutex_lock(philos->write_lock);
	if (!is_dead())
		printm(philos->id, action, philos->start_time);
	if (action == DIED)
		printm(philos->id, DIED, philos->start_time);
	pthread_mutex_unlock(philos->write_lock);
}

void	print_mutex(t_philo *philos, bool mutex)
{
	if (mutex == FALSE)
	{
		pthread_mutex_unlock(&philos->own.fork);
		pthread_mutex_unlock(philos->friend.fork);
		return ;
	}
	if (mutex == TRUE)
	{
		pthread_mutex_lock(&philos->own.fork);
		print_action(philos, TAKE);
		pthread_mutex_lock(philos->friend.fork);
		print_action(philos, TAKE);
	}
}
