/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:33:10 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/12 17:47:08 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int nb)
{
	if (nb > 47 && nb < 58)
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == ' '
		|| c == '\f')
		return (1);
	return (0);
}

static int	istheredigit(const char *str)
{
	int	i;
	int	check;

	check = FALSE;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = TRUE;
		i++;
	}
	if (str[i])
		return (FALSE);
	if (check == TRUE)
		return (TRUE);
	return (FALSE);
}

long	ft_atoil(const char *str)
{
	int		i;
	int		n;
	long	result;

	result = 0;
	i = 0;
	n = 0;
	while (ft_isspace(str[n]))
		n++;
	if (str[n] == '-' || str[n] == '+')
	{
		if (str[n] == '-')
			i++;
		n++;
	}
	while ((str[n] >= '0' && str[n] <= '9'))
		result = result * 10 + str[n++] - '0';
	if (!istheredigit(str))
		return (NOINT_ER);
	if (result > INT_MAX || result < INT_MIN || i > 1)
		return (ATOL_ER);
	if (i % 2 == 1)
		return (-result);
	return (result);
}
