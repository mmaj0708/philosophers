/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:48:18 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/29 13:53:04 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			get_fork(t_list *list)
{
	pthread_mutex_lock(list->fork1);
	pthread_mutex_lock(list->fork2);
	printf("%ld : %d took fork one\n", gettime(g_time_start), list->philo_pos);
	printf("%ld : %d took fork two\n", gettime(g_time_start), list->philo_pos);
	return (TRUE);
}

int			get_eat(t_list *list)
{
	list->stat = 1;
	printf("%ld : %d is eating\n", gettime(g_time_start), list->philo_pos);
	list->tla = gettime(g_time_start) + list->ttd;
	ft_wait(list->tte);
	if (list->n_meal != -1)
		list->n_meal--;
	pthread_mutex_unlock(list->fork1);
	pthread_mutex_unlock(list->fork2);
	if (list->n_meal == 0)
		return (FALSE);
	return (TRUE);
}

int			get_sleep(t_list *list)
{
	list->stat = 2;
	printf("%ld : %d is sleeping\n", gettime(g_time_start), list->philo_pos);
	ft_wait(list->tts);
	return (TRUE);
}

int			get_think(t_list *list)
{
	printf("%ld : %d is thinking\n", gettime(g_time_start), list->philo_pos);
	return (TRUE);
}
