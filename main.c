/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:50:44 by mmaj              #+#    #+#             */
/*   Updated: 2021/02/23 16:42:31 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


struct s_philo
{

}	typedef	t_philo;


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

void	*philo_life(void *lst)
{
	t_list *list;
	long int next_tte;
		// printf("check\n");

	list = lst;
	while (1)
	{
		pthread_mutex_lock(&lock);
		printf("\033[0;31m %ld : philo %d is eating\n", gettime(g_time_start), list->philo_pos);
		usleep(list->tte);
		pthread_mutex_unlock(&lock);

		// pthread_mutex_lock(&lock);
		printf("\033[0;31m %ld : philo %d is sleeping\n", gettime(g_time_start), list->philo_pos);
		usleep(list->tts);
		// pthread_mutex_unlock(&lock);
		
		// printf("%ld : philo is thinking\n", gettime(start));
		// usleep(1000000);
	}
	return (0);
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

void check_list(t_list *list)
{
	while (list != NULL)
	{
		printf("list->philo_pos = %d\n", list->philo_pos);
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
	while(list != NULL)
	{
	// printf("n_philo = %d\n", n_philo--);
		save = list;
		list = list->next;
		free(save);
	}
	return;
}

int	launch_philo(t_list	*list)
{
	while (list != NULL)
	{

		pthread_create(&list->th, NULL, philo_life, (void *)list);
		
		if (list->next == NULL)
			pthread_join(list->th, NULL);
		list = list->next;
	}
	return (0);
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

	// check_list(head_list);

	launch_philo(head_list);

	free_list(head_list, n_philo);

	// pthread_create(&thread1, NULL, philo_life, &t);
	// pthread_create(&thread2, NULL, philo_life, &t);
	// pthread_create(&thread3, NULL, philo_life, &t);

	// pthread_join(thread1, NULL);
}
