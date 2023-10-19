/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:55:27 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/12 17:45:03 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_forint(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && !ft_isspace(argv[i][j]) &&
				argv[i][j] != '-' && argv[i][j] != '+')
				return (ERROR);
			j++;
		}
		i++;
	}
	return (TRUE);
}

static int	check_convert(int argc, char **argv)
{
	int		size;
	long	check;

	size = 1;
	while (size < argc)
	{
		check = ft_atoil(argv[size]);
		if (check == ATOL_ER)
			return (printerror(ATOL_ERR));
		if (check == NOINT_ER)
			return (printerror(FORMAT_ERR));
		if (check < 0)
			return (printerror(MIN_ERR));
		if (check == 0 && size != 5)
			return (printerror(MIN_ERR));
		if (check < 60 && size < 5 && size > 1)
			return (printerror(MIN_ERR));
		if (check > 200 && size == 1)
			return (printerror(MAX_ERR));
		size++;
	}
	return (TRUE);
}

int	check_arg(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printerror(ARG_NB_ERR));
	if (check_forint(argc, argv) == ERROR)
		return (printerror(FORMAT_ERR));
	if (check_convert(argc, argv) == ERROR)
		return (ERROR);
	return (TRUE);
}

int	convert_arg(int index, char **argv)
{
	int	check;

	check = (int)ft_atoil(argv[index]);
	return (check);
}
