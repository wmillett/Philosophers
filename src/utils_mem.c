/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:06:28 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/12 17:47:01 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_program	*data(void)
{
	static t_program	a;

	return (&a);
}

int	check_malloc(void *a, void *b, void *c, int type)
{
	if (type == 3)
	{
		if (a == NULL || b == NULL || c == NULL)
			return (escape(a, b, c, MEM_ERR));
	}
	if (type == 2)
	{
		if (a == NULL || b == NULL)
			return (escape(a, b, c, MEM_ERR));
	}
	if (type == 1)
	{
		if (a == NULL)
			return (escape(a, b, c, MEM_ERR));
	}
	return (FALSE);
}
