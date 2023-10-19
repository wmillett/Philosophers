/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:48:51 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/17 22:40:11 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	one_philo(void *info)
{
	t_philo	*philos;

	philos = (t_philo *)info;
	philos->start_time = now();
	printm(philos->id, THINK, philos->start_time);
	pthread_mutex_lock(&philos->own.fork);
	printm(philos->id, TAKE, philos->start_time);
	while (now() - philos->start_time < data()->time_to_die)
		;
	return (printm(philos->id, DIED, philos->start_time));
}

int	set_one_philo(void)
{
	if (pthread_create(&data()->philos[0].thread, NULL, (void *)one_philo,
			&data()->philos[0]))
		return (printerror(THREAD_ERR));
	pthread_join(data()->philos[0].thread, NULL);
	return (DIED);
}
