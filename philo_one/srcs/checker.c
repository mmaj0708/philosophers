/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:03:37 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/30 10:46:29 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		check_param(t_param *param)
{
	printf("check param\n");
	printf("param->n_philo = %d\n", param->n_philo);
	printf("param->ttd = %d\n", param->ttd);
	printf("param->tte = %d\n", param->tte);
	printf("param->tts = %d\n", param->tts);
	printf("param->meal = %d\n", param->n_meal);
}

void		check_list_elmt(t_list *list, int n_philo)
{
	while (n_philo > 0)
	{
		printf("check list\n");
		printf("list->philo_pos = %d\n", list->philo_pos);
		printf("list->n_philo = %d\n", list->n_philo);
		printf("list->ttd = %d\n", list->ttd);
		printf("list->tte = %d\n", list->tte);
		printf("list->tts = %d\n", list->tts);
		printf("list->meal = %d\n", list->n_meal);
		printf("list->alive = %d\n", list->alive);
		printf("list->mut_print = %p\n", list->mut_print);
		printf("list->fork1 = %p\n", list->fork1);
		printf("list->fork2 = %p\n", list->fork2);
		n_philo--;
		list = list->next;
	}
}

void		check_fork_assignation(t_list *list, int n_philo)
{
	while (n_philo > 0)
	{
		printf("philo %d :\n", list->philo_pos);
		printf("fork1 adress = %p\n", list->fork1);
		printf("fork2 adress = %p\n", list->fork2);
		list = list->next;
		n_philo--;
	}
}

void		check_list(t_list *list)
{
	while (list != NULL)
	{
		printf("list->checker = %d\n", list->checker);
		list = list->next;
	}
}
