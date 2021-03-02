/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:06:01 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/02 12:16:22 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		init_fork(int n_philo, t_list *list)
{
	sem_t			*sem;

	sem = malloc(sizeof(pthread_mutex_t) * n_philo);
	pthread_mutex_init(&sem[sem_index], NULL);
// semaphre partagé
}

t_list		*lstnew(int i, t_param *param, int n_meal)
{
	t_list	*new;

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
	return (head_list);
}
