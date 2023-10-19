/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:06:30 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:04:25 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//  int DEBUG = 0;// --------------------

void	set_param(t_param *params, int argc, char **argv)
{
	int	i;
	int	j;
	int	tmp;

	j = 0;
	i = 1;
	while (i < argc)
	{
		tmp = ft_atoil(argv[i]);
		params->u_param.param[j++] = tmp;
		i++;
	}
	if (argc == 5)
		params->u_param.param[4] = -1;
}

int	main(int argc, char **argv)
{
	t_param	*params;

	if (check_arg(argc, argv) == ERROR)
		return (ERROR);
	params = malloc(sizeof(int) * 5);
	if (check_malloc(params, NULL, NULL, 1) == ERROR)
		return (ERROR);
	set_param(params, argc, argv);
	data()->mutex_flag = 0;
	if (set_philo(params) == ERROR)
		return (escape(params, NULL, NULL, NULL));
	return (leave(params, NULL, NULL, data()->philos[0].start_time));
}
