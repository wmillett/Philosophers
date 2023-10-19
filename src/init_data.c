/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:04:19 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 13:57:50 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_threads(void)
{
	int	i;

	i = 0;
	while (i < data()->nb_philos)
	{
		pthread_join(data()->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data()->reaper_thread, NULL);
}

static int	init_philo(t_param *params)
{
	int	i;

	i = 0;
	data()->nb_philos = params->u_param.param[0];
	if (init_mutex(params) == ERROR)
		return (ERROR);
	data()->to_eat = params->u_param.param[4];
	data()->time_to_die = params->u_param.param[1];
	data()->time_to_eat = params->u_param.param[2];
	data()->time_to_sleep = params->u_param.param[3];
	while (i < params->u_param.param[0])
	{
		data()->philos[i].id = i + 1;
		data()->philos[i].nb_to_eat = params->u_param.param[4];
		data()->philos[i].action = THINK;
		data()->philos[i].action_start = now();
		i++;
	}
	return (TRUE);
}

int	multiple_philo(t_param *params)
{
	int	i;

	i = 0;
	while (i < params->u_param.param[0])
	{
		if (pthread_create(&data()->philos[i].thread, NULL, (void *)routine,
				&data()->philos[i]))
			return (printerror(THREAD_ERR));
		i++;
	}
	if (pthread_create(&data()->reaper_thread, NULL, (void *)the_reaper, NULL))
		return (printerror(THREAD_ERR));
	pthread_mutex_lock(&data()->start_lock);
	data()->start_flag = TRUE;
	pthread_mutex_unlock(&data()->start_lock);
	wait_threads();
	return (FINISH);
}

int	set_philo(t_param *params)
{
	if (init_philo(params) == ERROR)
		return (ERROR);
	set_start_time(params);
	data()->start_flag = FALSE;
	if (params->u_param.param[0] == 1)
	{
		if (set_one_philo() == DIED)
			return (DIED);
		return (FINISH);
	}
	else
	{
		if (multiple_philo(params) == ERROR)
		{
			pthread_mutex_lock(&data()->start_lock);
			data()->start_flag = ERROR;
			pthread_mutex_unlock(&data()->start_lock);
			usleep(2000);
			return (ERROR);
		}
	}
	return (FINISH);
}
