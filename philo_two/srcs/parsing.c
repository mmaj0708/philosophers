/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:31:42 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/02 10:29:19 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			check_only_digit(char **av, int ac)
{
	int i;
	int	j;

	i = 1;
	while (i <= 4)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit((int)av[i][j]) == 0)
				return (FAILURE);
			j++;
		}
		i++;
	}
	j = 0;
	if (ac == 6)
		while (av[5][j])
		{
			if (ft_isdigit((int)av[i][j]) == 0)
				return (FAILURE);
			j++;
		}
	return (0);
}

int			check_good_value(t_param *param, int ac)
{
	if (param->n_philo < 1 || param->ttd < 1
	|| param->tte < 1 || param->tts < 1)
		return (FAILURE);
	if (ac == 6 && param->n_meal < 1)
		return (FAILURE);
	return (0);
}

int			check_arg_digit(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("error : incorrect number of arguments\n");
		return (FAILURE);
	}
	if (check_only_digit(av, ac) == FAILURE)
	{
		printf("error : only digits authorized\n");
		return (FAILURE);
	}
	return (0);
}

t_param		*parsing(int ac, char **av)
{
	t_param	*param;

	if (check_arg_digit(ac, av) == FAILURE)
		return (NULL);
	param = malloc(sizeof(param));
	param->n_philo = ft_atoi(av[1]);
	param->ttd = ft_atoi(av[2]);
	param->tte = ft_atoi(av[3]);
	param->tts = ft_atoi(av[4]);
	if (ac == 6)
		param->n_meal = ft_atoi(av[5]);
	else
		param->n_meal = -1;
	if (check_good_value(param, ac) == FAILURE)
	{
		printf("error : bad value(s)\n");
		free(param);
		return (NULL);
	}
	return (param);
}
