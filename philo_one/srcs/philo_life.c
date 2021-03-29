/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:49:37 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/29 14:12:09 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		*philo_life(void *lst)
{
	t_list *list;

	list = lst;
	while (1)
	{
		get_fork(list);
		if (get_eat(list) == FALSE)
		{
			g_philo_ate++;
			return (0);
		}
		get_sleep(list);
		get_think(list);
	}
	return (0);
}

int			death_checker(t_list *list, int n_philo)
{
	t_list		*save;
	t_list		*last_philo;
	int			i;

	save = list;
	i = 0;
	while (1)
	{
		if ((gettime(g_time_start) >= list->tla) || g_philo_ate == n_philo)
		{
			last_philo = list;
			if (g_philo_ate == n_philo)
				g_eatordeath = 1;
			else
				g_eatordeath = 0;
			break ;
		}
		list = list->next;
	}
	if (g_eatordeath == 0)
		printf("%ld : %d DIED\n", gettime(g_time_start), last_philo->philo_pos);
	if (g_eatordeath == 1)
		printf("%ld : philos ate their meals!!!\n", gettime(g_time_start));
	return (0);
}

int			first_launch(t_list *list, int n_philo)
{
	int i;

	i = 0;
	while (i < n_philo && (list->philo_pos % 2))
	{
		list->tla = gettime(g_time_start) + list->ttd;
		pthread_create(&list->th, NULL, philo_life, (void *)list);
		list = list->next;
		list = list->next;
		i = i + 2;
	}
	return (0);
}

int			launch_philo(t_list *list, int n_philo)
{
	t_list	*save;
	int		i;

	save = list;
	i = 0;
	make_list_loop(list);
	first_launch(list, n_philo);
	list = save;
	list = list->next;
	usleep(1000);
	while (i < n_philo && !(list->philo_pos % 2))
	{
		list->tla = gettime(g_time_start) + list->ttd;
		pthread_create(&list->th, NULL, philo_life, (void *)list);
		list = list->next;
		list = list->next;
		i = i + 2;
	}
	death_checker(save, n_philo);
	return (0);
}
