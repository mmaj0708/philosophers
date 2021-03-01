/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:50:44 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/01 14:06:34 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_param(t_param *param)
{
	printf("check param\n");
	printf("param->n_philo = %d\n", param->n_philo);
	printf("param->ttd = %d\n", param->ttd);
	printf("param->tte = %d\n", param->tte);
	printf("param->tts = %d\n", param->tts);
	printf("param->meal = %d\n", param->n_meal);
}

void	check_list_elmt(t_list *list, int n_philo)
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
		n_philo--;
		list = list->next;
	}
}

void	check_fork_assignation(t_list *list, int n_philo)
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

int	ft_atoi(char *str)
{
	long			i;
	long			sign;
	unsigned int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' ||
	str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + str[i] - 48;
		i++;
	}
	return ((int)(nb * sign));
}

void check_list(t_list *list)
{
	while (list != NULL)
	{
		printf("list->checker = %d\n", list->checker);
		list = list->next;
	}
}

void	free_list(t_list *list, int n_philo)
{
	t_list *save;

	if (!list)
		return;
	if (n_philo == 0)
		return;
	save = list;
	// printf("save->philo_pos = %d\n", save->philo_pos);
	while(n_philo > 0)
	{
	// printf("n_philo = %d\n", n_philo--);
		save = list;
		list = list->next;
		free(save);
		n_philo--;
	}
	return;
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

t_list	*lstnew(int i, t_param *param, int n_meal)
{
	t_list	*new;

	new = malloc(sizeof(t_list)); // free!
	new->ttd = param->ttd;
	new->tte = param->tte;
	new->tts = param->tts;
	new->n_meal = n_meal;
	new->philo_pos = i;
	new->alive = TRUE;
	new->next = NULL;

	return (new);
}

void	make_list_loop(t_list *list)
{
	t_list	*save;

	save = list;
	while (list->next != NULL)
		list = list->next;
	list->next = save;
}

int	launch_philo(t_list	*list, int n_philo)
{
	t_list	*save;
	int		i;

	save = list;
	i = 0;
	make_list_loop(list);
	// check_list_elmt(list, n_philo);
	// check_fork_assignation(list, n_philo);
	while (i < n_philo)
	{
		list->stat = 3;
		list->tla = gettime(g_time_start) + list->ttd;
		pthread_create(&list->th, NULL, philo_life, (void *)list);
		// printf("check nb thread\n");
		list = list->next;
		i++;
	}
	// pthread_join(save->th, NULL);
	death_checker(save, n_philo);
	return (0);
}

void	affect_fork(int n_philo, t_list *list)
{
	int				lock_index;
	pthread_mutex_t *lock;

	lock_index = 0;
	lock = malloc(sizeof(pthread_mutex_t) * n_philo);
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
}

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		check_only_digit(char **av, int ac)
{
	int i;
	int	j;

	i = 1;
	while (i <= 4)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit((int)av[i][j]) == 0)
				return (FAILURE);
			j++;
		}
		i++;
	}
	j = 0;
	if (ac == 6)
		while (av[5][j])
		{
			if (ft_isdigit((int)av[i][j]) == 0)
				return (FAILURE);
			j++;
		}
	return (0);
}

int		check_good_value(t_param *param, int ac)
{
	if (param->n_philo < 1 || param->ttd < 1
	|| param->tte < 1 || param->tts < 1)
		return (FAILURE);
	if (ac == 6 && param->n_meal < 1)
		return (FAILURE);
	return (0);
}

t_param	*parsing(int ac, char **av)
{
	t_param	*param;

	if (ac < 5 || ac > 6)
	{
		printf("error : incorrect number of arguments\n");
		return (NULL);
	}
	if (check_only_digit(av, ac) == FAILURE)
	{
		printf("error : only digits authorized\n");
		return (NULL);
	}
	param = malloc(sizeof(param));
	param->n_philo = ft_atoi(av[1]);
	param->ttd = ft_atoi(av[2]);
	param->tte = ft_atoi(av[3]);
	param->tts = ft_atoi(av[4]);
	if (ac == 6)
		param->n_meal = ft_atoi(av[5]);
	else
		param->n_meal = -1;
	// check_param(param);
	if (check_good_value(param, ac) == FAILURE)
	{
		printf("error : bad value(s)\n");
		free (param);
		return (NULL);
	}
	return (param);
}

int	destroy_all(t_list *list, int n_philo)
{
	int i;

	i = 0;
	while (i < n_philo)
	{
		pthread_detach(list->th);
		pthread_mutex_destroy(list->fork1);
		list = list->next;
		i++;
	}
	list = list->next;
	free(list->fork1);
	return (0);
}

int main(int ac, char **av)
{
	struct timeval	start;
	t_list			*list;
	t_list			*head_list;
	int				i = 1;
	t_param			*param;
	int				n_meal;

	list = NULL;

	g_philo_ate = 0;
	param = parsing(ac, av);
	if (param == NULL)
		return (0);

	// check_param(param);

	pthread_mutex_init(&lock, NULL);

	gettimeofday(&g_time_start, NULL);

	n_meal = param->n_meal;
	// printf("check param->meal = %d\n", param->n_meal);
	while (i <= param->n_philo)
	{
		if (list == NULL)
		{
			list = lstnew(i, param, n_meal);
			head_list = list;
		}
		else
		{
			list->next = lstnew(i, param, n_meal);
			list = list->next;
		}
		i++;

	}

	affect_fork(param->n_philo, head_list);

	// check_list(head_list);

	// check_list_elmt(head_list, param->n_philo);

	launch_philo(head_list, param->n_philo);

	destroy_all(head_list, param->n_philo);
	
	free_list(head_list, param->n_philo);
	free(param);
}

// placer une var alive dans t_list verifiée TRUE chaque fois au debut de nouvelle action
// le death_checker set alive à false qd ya un mort
// evite tout ecriture en trop !