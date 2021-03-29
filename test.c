/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:32:19 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/29 11:32:31 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void	*check(void *arg)
{
	printf("IN check\n");

	exit(15);
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

int main()
{
	int stat;
	int ret;
	pid_t	pid;
	pthread_t		th;
	pthread_mutex_t lock;
	struct timeval start;
	// struct timeval curr;

	// if ((pid = fork()) == 0)
	// {	
	// // 	pthread_create(&th, NULL, check, NULL);
	// // pthread_join(th, NULL);
	// 	check(NULL);
	// }

	// waitpid(pid, &stat, 0);
	// ret = WEXITSTATUS(stat);
	// printf("stat = %d\n", ret);
	// pthread_mutex_init(&lock, NULL);

	// check(NULL);

	gettimeofday(&start, NULL);
	
	int tts = 200;
	int limite = tts;

	while (1)
	{
		while (gettime(start) < limite)
		{
			usleep(100);
		}
		printf("time = %ld\n", gettime(start));
		limite = limite + tts;
	}



	// getchar();


	// pthread_detach(th);
	return (0);
}