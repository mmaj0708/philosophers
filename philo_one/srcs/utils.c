/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:28:45 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/29 12:12:27 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			ft_atoi(char *str)
{
	long			i;
	long			sign;
	unsigned int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' ||
	str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + str[i] - 48;
		i++;
	}
	return ((int)(nb * sign));
}

int			ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void		ft_wait(int time_to_wait)
{
	time_to_wait = gettime(g_time_start) + time_to_wait;
	while (gettime(g_time_start) < time_to_wait)
	{
		usleep(100);
	// printf("time = %ld\n", gettime(g_time_start));
	}
}