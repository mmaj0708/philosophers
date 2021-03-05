/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:32:19 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/05 14:45:46 by mmaj             ###   ########.fr       */
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

int main()
{
	int stat;
	int ret;
	pid_t	pid;
	pthread_t		th;
	pthread_mutex_t lock;

	if ((pid = fork()) == 0)
	{	
	// 	pthread_create(&th, NULL, check, NULL);
	// pthread_join(th, NULL);
		check(NULL);
	}

	waitpid(pid, &stat, 0);
	ret = WEXITSTATUS(stat);
	printf("stat = %d\n", ret);
	// pthread_mutex_init(&lock, NULL);

	// check(NULL);

	printf("in main\n");
	// getchar();


	// pthread_detach(th);
	return (0);
}