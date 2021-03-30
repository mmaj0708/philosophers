/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:50:44 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/30 11:31:29 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		free_list(t_list *list, int n_philo)
{
	t_list *save;

	if (!list)
		return ;
	if (n_philo == 0)
		return ;
	save = list;
	while (n_philo > 0)
	{
		save = list;
		list = list->next;
		free(save);
		n_philo--;
	}
	return ;
}

long int	gettime(struct timeval start)
{
	struct timeval	curr;
	long int		time;

	gettimeofday(&curr, NULL);
	time = curr.tv_sec - start.tv_sec;
	time = time * 1000000;
	curr.tv_usec = curr.tv_usec - start.tv_usec;
	time = time + curr.tv_usec;
	time = time / 1000;
	return (time);
}

void		make_list_loop(t_list *list)
{
	t_list	*save;

	save = list;
	while (list->next != NULL)
		list = list->next;
	list->next = save;
}

int			destroy_all(t_list *list, int n_philo)
{
	int i;

	i = 0;
	while (i < n_philo)
	{
		pthread_detach(list->th);
		list = list->next;
		i++;
	}
	list = list->next;
	sem_unlink("GNE");
	return (0);
}

int			main(int ac, char **av)
{
	t_list			*list;
	t_list			*head_list;
	t_param			*param;
	int				n_meal;

	g_philo_ate = 0;
	param = parsing(ac, av);
	if (param == NULL)
		return (0);
	gettimeofday(&g_time_start, NULL);
	n_meal = param->n_meal;
	if (!(list = create_philo(param, list, param->n_philo, n_meal)))
		return (0);
	head_list = list;
	if (init_fork(param->n_philo, head_list) == FAILURE)
		return (0);
	launch_philo(head_list, param->n_philo);
	destroy_all(head_list, param->n_philo);
	free_list(head_list, param->n_philo);
	free(param);
}
