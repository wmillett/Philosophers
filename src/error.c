/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:41:07 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:03:04 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	printerror(char *str)
{
	printf("\033[0;31mError: %s\033[0m\n", str);
	return (ERROR);
}

static void	sub_destroy_mutex(void)
{
	while (data()->mutex_flag > 4 + (data()->nb_philos * 3))
	{
		pthread_mutex_destroy(&data()->philos[data()->mutex_flag - (4
				+ (data()->nb_philos * 2))].last_lock);
		data()->mutex_flag -= 1;
	}
	while (data()->mutex_flag > 4 + (data()->nb_philos * 2))
	{
		pthread_mutex_destroy(&data()->philos[data()->mutex_flag - (4
				+ (data()->nb_philos * 2))].meal_lock);
		data()->mutex_flag -= 1;
	}
	while (data()->mutex_flag > 4 + data()->nb_philos)
	{
		pthread_mutex_destroy(&data()->philos[data()->mutex_flag - (4
				+ data()->nb_philos)].action_lock);
		data()->mutex_flag -= 1;
	}
}

void	destroy_mutex(void)
{
	sub_destroy_mutex();
	while (data()->mutex_flag > 4)
	{
		pthread_mutex_destroy(&data()->philos[data()->mutex_flag - 4].own.fork);
		data()->mutex_flag -= 1;
	}
	if (data()->mutex_flag == 4)
		pthread_mutex_destroy(&data()->last_lock);
	if (data()->mutex_flag >= 3)
		pthread_mutex_destroy(&data()->start_lock);
	if (data()->mutex_flag >= 2)
		pthread_mutex_destroy(&data()->write_lock);
	if (data()->mutex_flag >= 1)
		pthread_mutex_destroy(&data()->dead_lock);
}

int	escape(void *a, void *b, void *c, char *err_msg)
{
	if (data()->mutex_flag)
		destroy_mutex();
	free(a);
	free(b);
	free(c);
	if (err_msg)
		printerror(err_msg);
	return (ERROR);
}

int	leave(void *a, void *b, void *c, uint64_t time)
{
	uint64_t	current;

	current = now();
	printf("\033[1;32mEnd of simulation: %llums\033[0m\n", current - time);
	printf("\033[1;32mAverage number of meals eaten: %d\033[0m\n",
		data()->to_eat - data()->philos[0].nb_to_eat);
	if (data()->mutex_flag)
		destroy_mutex();
	free(a);
	free(b);
	free(c);
	return (FINISH);
}
