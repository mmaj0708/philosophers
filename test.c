/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:32:19 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/02 09:17:47 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void	*check(void *arg)
{
	usleep(3000000);
	return (NULL);
}

int main()
{
	int *i = malloc(45);
	i = malloc(45);
	pthread_mutex_t lock;
	pthread_t		th;

	pthread_mutex_init(&lock, NULL);

	// check(NULL);

	// printf("check\n");
	// pthread_create(&th, NULL, check, NULL);
	getchar();

	// pthread_join(th, NULL);

	// pthread_detach(th);
	return (0);
}