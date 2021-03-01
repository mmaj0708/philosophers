/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 09:49:37 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/01 13:40:14 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>


int		get_fork(t_list *list)
{
	pthread_mutex_lock(list->fork1);
	pthread_mutex_lock(list->fork2);
	printf("%ld : philo %d has taken fork one\n", gettime(g_time_start), list->philo_pos);
	printf("%ld : philo %d has taken fork two\n", gettime(g_time_start), list->philo_pos);
	return (TRUE);
}

int		get_eat(t_list *list)
{
	list->stat = 1;
	printf("%ld : philo %d is eating\n", gettime(g_time_start), list->philo_pos);
	list->tla = gettime(g_time_start) + list->ttd;
	usleep(list->tte * 1000);
	if (list->n_meal != -1)
	{
		list->n_meal--;
		// printf("meal left for philo %d = %d\n", list->philo_pos, list->n_meal);
	}
	pthread_mutex_unlock(list->fork1);
	pthread_mutex_unlock(list->fork2);
	if (list->n_meal == 0)
		return (FALSE);
	return (TRUE);
}

int		get_sleep(t_list *list)
{
	list->stat = 2;
	printf("%ld : philo %d is sleeping\n", gettime(g_time_start), list->philo_pos);
	usleep(list->tts * 1000);
	return (TRUE);
}

int		get_think(t_list *list)
{
	printf("%ld : philo %d is thinking\n", gettime(g_time_start), list->philo_pos);
	return (TRUE);
}

void	*philo_life(void *lst)
{
	t_list *list;
	long int next_tte;

	list = lst;
	while (1)
	{
		// if (list->alive == FALSE)
		// 	return (0);
		get_fork(list);
		// if (list->alive == FALSE)
		// 	return (0);
		if (get_eat(list) == FALSE)
		{
			g_philo_ate++;
			// printf("check g_philo_ate == %d\n", g_philo_ate);
			return (0);
		}
	// printf("%ld : philo %d tla = %d\n", gettime(g_time_start), list->philo_pos, list->tla);
		// if (list->alive == FALSE)
		// 	return (0);
		get_sleep(list);
		// if (list->alive == FALSE)
		// 	return (0);
		get_think(list);
	}
	return (0);
}

int	death_checker(t_list *list, int n_philo)
{
	t_list *save;
	t_list *last_philo;
	int i;

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
			// printf("list->philo_pos = %d, list->stat = %d, gettime = %ld, list->tla = %d\n", last_philo->philo_pos, last_philo->stat, gettime(g_time_start), last_philo->tla);
			// printf("g_ph_ate = %d\n", g_philo_ate);
			if (g_eatordeath == 0)
			while (i < n_philo)
			{
				list->alive = FALSE;
				list = list->next;
				i++;
			}
			break;
		}
		list = list->next;
	}
	if (g_eatordeath == 0)
		printf("%ld : philo %d died!!!\n", gettime(g_time_start), last_philo->philo_pos);
	if (g_eatordeath == 1)
		printf("%ld : philos ate their meals!!!\n", gettime(g_time_start));
	return (0);
}
