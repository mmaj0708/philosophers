/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:06:01 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/30 12:31:32 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <errno.h>

int			init_fork(int n_philo, t_list *list)
{
	sem_t			*sem;
	sem_t			*sem_print;
	int				i;

	i = 0;
	sem_unlink("GNE");
	sem_unlink("OK");
	if ((sem_print = sem_open("OK", O_CREAT, 644, 1)) == SEM_FAILED)
	{
		printf("CHECK %s\n", strerror(errno));
		return (FAILURE);
	}
	if ((sem = sem_open("GNE", O_CREAT, 644, n_philo)) == SEM_FAILED)
		return (FAILURE);
	while (i < n_philo)
	{
		list->sem = sem;
		list->sem_print = sem_print;
		list = list->next;
		i++;
	}
	return (0);
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
