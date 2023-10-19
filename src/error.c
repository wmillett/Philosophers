/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:41:07 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:49:34 by wmillett         ###   ########.fr       */
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
	while (data()->mflag_meal)
	{
		pthread_mutex_destroy(&data()->philos[data()->mflag_meal
			- 1].meal_lock);
		data()->mflag_meal--;
	}
	while (data()->mflag_action)
	{
		pthread_mutex_destroy(&data()->philos[data()->mflag_action
			- 1].action_lock);
		data()->mflag_action--;
	}
	while (data()->mflag_fork)
	{
		pthread_mutex_destroy(&data()->philos[data()->mflag_fork - 1].own.fork);
		data()->mflag_fork--;
	}
}

void	destroy_mutex(void)
{
	sub_destroy_mutex();
	if (data()->mflag_data == 3)
		pthread_mutex_destroy(&data()->start_lock);
	if (data()->mflag_data >= 2)
		pthread_mutex_destroy(&data()->write_lock);
	if (data()->mflag_data >= 1)
		pthread_mutex_destroy(&data()->dead_lock);
}

int	escape(void *a, void *b, void *c, char *err_msg)
{
	if (data()->mflag)
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
	if (data()->mflag)
		destroy_mutex();
	free(a);
	free(b);
	free(c);
	return (FINISH);
}
