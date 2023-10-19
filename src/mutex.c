/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:53:07 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:51:23 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static void assign_ptr(void)
// {
// 	int i;

// 	i = 0;
// 	while(i < data()->nb_philos)
// 	{
// 		data()->philos[i].last_lock = &data()->philos[i].last_mutex;
// 		data()->philos[i].meal_lock = &data()->philos[i].meal_mutex;
// 		i++;
// 	}
// }

static int	init_action(void)
{
	int	i;

	i = 0;
	while (i < data()->nb_philos)
	{
		if (pthread_mutex_init(&data()->philos[i++].action_lock, NULL))
			return (ERROR);
		data()->mflag_action += 1;
	}
	i = 0;
	while (i < data()->nb_philos)
	{
		if (pthread_mutex_init(&data()->philos[i++].meal_lock, NULL))
			return (ERROR);
		data()->mflag_meal += 1;
	}
	i = 0;
	return (FINISH);
}

static void	r_fork_mutex(t_param *params)
{
	int	i;

	i = 0;
	while (i < params->u_param.param[0] && params->u_param.param[0] > 1)
	{
		if (i == params->u_param.param[0] - 1)
			data()->philos[i].friend.fork = &data()->philos[0].own.fork;
		else
			data()->philos[i].friend.fork = &data()->philos[i + 1].own.fork;
		i++;
	}
}

static int	philo_mutex(t_param *params)
{
	int	i;

	i = 0;
	while (i < params->u_param.param[0])
	{
		if (pthread_mutex_init(&data()->philos[i].own.fork, NULL))
			return (ERROR);
		data()->mflag_fork += 1;
		data()->philos[i].write_lock = &data()->write_lock;
		data()->philos[i].dead_lock = &data()->dead_lock;
		i++;
	}
	if (init_action() == ERROR)
		return (ERROR);
	r_fork_mutex(params);
	return (TRUE);
}

int	init_mutex(t_param *params)
{
	data()->mflag_action = 0;
	data()->mflag_meal = 0;
	data()->mflag_fork = 0;
	data()->mflag_data = 0;
	if (pthread_mutex_init(&data()->dead_lock, NULL))
		return (printerror(MUTEX_ERR));
	data()->mflag_data += 1;
	data()->mflag = TRUE;
	if (pthread_mutex_init(&data()->write_lock, NULL))
		return (printerror(MUTEX_ERR));
	data()->mflag_data += 1;
	if (pthread_mutex_init(&data()->start_lock, NULL))
		return (printerror(MUTEX_ERR));
	data()->mflag_data += 1;
	if (philo_mutex(params) == ERROR)
		return (printerror(MUTEX_ERR));
	return (TRUE);
}
