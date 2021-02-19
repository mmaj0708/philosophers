/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:50:44 by mmaj              #+#    #+#             */
/*   Updated: 2021/02/19 16:57:50 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int main()
{

	struct timeval curr;
	struct timeval start;

	gettimeofday(&start, NULL);

	while (1)
	{
		gettimeofday(&curr, NULL);
		printf("time_t = %ld\n", curr.tv_sec);
		printf("suseconds_t = %d\n", curr.tv_usec);
		
		printf("time_spend = %d\n", curr.tv_usec);
		
		usleep(200000);
	}
}