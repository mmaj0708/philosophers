/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:49:37 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/29 15:51:38 by mmaj             ###   ########.fr       */
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
		get_eat(list);
		get_sleep(list);
		get_think(list);
	}
}

void		*death_checker(void *lst)
{
	t_list		*list;
	int			i;

	list = (t_list *)lst;
	i = 0;
	while (1)
	{
		if ((gettime(g_time_start) > list->tla) || list->n_meal == 0)
		{
			if (list->n_meal == 0)
				g_eatordeath = ATE;
			else
				g_eatordeath = DEATH;
			break ;
		}
	}
	if (g_eatordeath == DEATH)
	{
		sem_wait(list->sem_print);
		printf("%ld : %d died\n", gettime(g_time_start), list->philo_pos);
		exit(DEATH);
	}
	if (g_eatordeath == ATE)
		exit(ATE);
	return (NULL);
}

void		make_list_loop(t_list *list)
{
	t_list	*save;

	save = list;
	while (list->next != NULL)
		list = list->next;
	list->next = save;
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
			pthread_create(&list->th, NULL, death_checker, (void *)list);
			philo_life(list);
		}
		list = list->next;
		i++;
	}
	return (0);
}
