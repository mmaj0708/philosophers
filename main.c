/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:50:44 by mmaj              #+#    #+#             */
/*   Updated: 2021/02/24 12:43:31 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_list	*lstnew(int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list)); // free!
	new->ttd = TTD;
	new->tte = TTE;
	new->tts = TTS;
	new->philo_pos = i;
	new->next = NULL;

	return (new);
}

void	*philo_life(void *lst)
{
	t_list *list;
	long int next_tte;
		// printf("check\n");

	list = lst;
	while (1)
	{
		list->stat = 3;
		pthread_mutex_lock(list->fork1);
		printf("%ld : philo %d has taken fork one\n", gettime(g_time_start), list->philo_pos);
		pthread_mutex_lock(list->fork2);
		list->stat = 1;
		printf("%ld : philo %d has taken fork two\n", gettime(g_time_start), list->philo_pos);
		printf("%ld : philo %d is eating\n", gettime(g_time_start), list->philo_pos);
		usleep(list->tte * 1000);
		pthread_mutex_unlock(list->fork1);
		pthread_mutex_unlock(list->fork2);
		
		list->stat = 2;
		list->tla = gettime(g_time_start) + list->ttd;
		printf("%ld : philo %d will die after %d\n", gettime(g_time_start), list->philo_pos, list->tla);
		printf("%ld : philo %d is sleeping\n", gettime(g_time_start), list->philo_pos);
		usleep(list->tts * 1000);
		
		printf("%ld : philo %d is thinking\n", gettime(g_time_start), list->philo_pos);
	}
	return (0);
}

int	death_checker(t_list *list)
{
	while (1)
	{
		printf("DEATH CHECKER \n");
		if (list->stat != 2 && gettime(g_time_start) >= list->tla)
			break;
		list = list->next;
	}
	// arreter tous les proccess;
	printf("%ld : philo %d died!!!\n", gettime(g_time_start), list->philo_pos);
	return (0);
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

	save = list;
	make_list_loop(list);
	while (n_philo > 0)
	{
		pthread_create(&list->th, NULL, philo_life, (void *)list);
		list = list->next;
		n_philo--;
	}
	death_checker(save);
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
		if (lock_index == 0)
		{
			list->fork1 = &lock[lock_index];
			list->fork2 = &lock[n_philo - 1];

			list->checker = lock_index;
			// printf("checker var = %d\n", list->checker);
			
			list = list->next;
			lock_index++;
		}
		else
		{
			list->fork1 = &lock[lock_index];
			list->fork2 = &lock[lock_index - 1];

			list->checker = lock_index;
			// printf("checker var = %d\n", list->checker);
			
			list = list->next;
			lock_index++;
		}
	}
}


int main()
{
	struct timeval	start;
	int				n_philo = 5;
	t_list			*list;
	t_list			*head_list;
	int				i = 1;

	list = NULL;

	pthread_mutex_init(&lock, NULL);

	gettimeofday(&g_time_start, NULL);

	// list = init_list(list);
	// init_philo
	while (i <= n_philo)
	{
		if (list == NULL)
		{
			list = lstnew(i);
			head_list = list;
		}
		else
		{
			list->next = lstnew(i);
			list = list->next;
		}
		i++;
	}
	// fin init_philo

	affect_fork(n_philo, head_list);

	// check_list(head_list);

	launch_philo(head_list, n_philo);

	free_list(head_list, n_philo);

}
