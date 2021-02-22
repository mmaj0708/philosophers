/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:50:44 by mmaj              #+#    #+#             */
/*   Updated: 2021/02/22 16:08:49 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

#define TTD 500000
#define TTE 500000
#define TTS 500000

struct timeval g_time_start;

struct s_time_option
{
	int ttd;
	int tte;
	int tts;
} typedef t_time_option;

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

void	*philo_two(t_time_option t)
{
	while (1)
	{
		printf("\033[0;32m %ld : philo two is eating\n", gettime(g_time_start));
		usleep(t.tte);
		printf("\033[0;32m %ld : philo two is sleeping\n", gettime(g_time_start));
		usleep(t.tts);
		// printf("%ld : philo is thinking\n", gettime(start));
		// usleep(1000000);
	}
	return (0);
}

void	*philo_one(void *t)
{
	t_time_option *t2;
	long int next_tte;

	t2 = t;
	while (1)
	{
		printf("\033[0;31m %ld : philo one is eating\n", gettime(g_time_start));
		usleep(t2->tte);
			
		printf("\033[0;31m %ld : philo one is sleeping\n", gettime(g_time_start));
		usleep(t2->tts);

		
		// printf("%ld : philo is thinking\n", gettime(start));
		// usleep(1000000);
	}
	return (0);
}

int main()
{
	struct timeval	start;
	t_time_option t;
	pthread_t newthread;

	t.ttd = TTD;
	t.tte = TTE;
	t.tts = TTS;

	gettimeofday(&g_time_start, NULL);

	pthread_create(&newthread, NULL, philo_one, &t);

	// philo_two(t);
	pthread_join(newthread, NULL);
	// philo_two(start, t);
}
