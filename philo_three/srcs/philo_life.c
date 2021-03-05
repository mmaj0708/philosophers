/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:49:37 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/05 14:55:23 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

void		*philo_life(void *lst)
{
	t_list *list;

	list = lst;
	while (1)
	{
		get_fork(list);
		if (get_eat(list) == FALSE)
		{
			usleep(20);
			return (0);
		}
		get_sleep(list);
		get_think(list);
	}
	return (0);
}

void		*death_checker(void *lst)
{
	t_list		*list;
	t_list		*save;
	int			i;

	list = (t_list *)lst;
	save = list;
	i = 0;
	while (1)
	{
		if ((gettime(g_time_start) >= list->tla) || list->n_meal == 0)
		{
			if (list->n_meal == 0)
				g_eatordeath = 1;
			else
				g_eatordeath = 0;
			break ;
		}
	}
	if (g_eatordeath == 0)
	{
		sem_wait(list->sem_print);
		printf("%ld : %d died\n", gettime(g_time_start), list->philo_pos);
		// free ??
		exit(0);
	}
	if (g_eatordeath == 1)
		exit(1); // free ??
	return (NULL);
}

int			launch_philo(t_list *list, int n_philo)
{
	t_list	*save;
	int		i;

	save = list;
	i = 0;
	make_list_loop(list);
	while (i < n_philo)
	{
		if ((list->pid = fork()) == 0)
		{
			list->stat = 3;
			list->tla = gettime(g_time_start) + list->ttd;
			pthread_create(&list->th, NULL, death_checker, (void *)save);
			philo_life(list);
		}
		list = list->next;
		i++;
	}
	return (0);
}
