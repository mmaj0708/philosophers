/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:06:01 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/30 11:19:44 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			affect_fork(int n_philo, t_list *list)
{
	int				lock_index;
	pthread_mutex_t *lock;

	lock_index = 0;
	if (!(lock = malloc(sizeof(pthread_mutex_t) * n_philo)))
		return (FAILURE);
	while (lock_index < n_philo)
	{
		pthread_mutex_init(&lock[lock_index], NULL);
		lock_index++;
	}
	lock_index = 0;
	while (list != NULL)
	{
		list->fork1 = lock + ((n_philo - 2 + list->philo_pos) % n_philo);
		list->fork2 = lock + list->philo_pos - 1;
		list->checker = list->philo_pos;
		list = list->next;
	}
	return (0);
}

t_list		*lstnew(int i, t_param *param, int n_meal)
{
	t_list			*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->ttd = param->ttd;
	new->tte = param->tte;
	new->tts = param->tts;
	new->n_meal = n_meal;
	new->philo_pos = i;
	new->alive = TRUE;
	new->next = NULL;
	return (new);
}

int			affect_mutprint(t_list *list, int n_philo)
{
	int				i;
	pthread_mutex_t	*mutex_print;

	i = 0;
	if (!(mutex_print = malloc(sizeof(pthread_mutex_t))))
		return (FAILURE);
	pthread_mutex_init(mutex_print, NULL);
	while (i < n_philo)
	{
		list->mut_print = mutex_print;
		list = list->next;
		i++;
	}
	return (0);
}

t_list		*create_philo(t_param *param, t_list *list, int n_philo, int n_meal)
{
	int				i;
	t_list			*head_list;

	i = 1;
	list = lstnew(i, param, n_meal);
	if (list == NULL)
		return (NULL);
	head_list = list;
	i++;
	while (i <= param->n_philo)
	{
		list->next = lstnew(i, param, n_meal);
		if (list == NULL)
			return (NULL);
		list = list->next;
		i++;
	}
	if (affect_mutprint(head_list, n_philo) == FAILURE)
		return (NULL);
	return (head_list);
}
