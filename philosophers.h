/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:50:54 by mmaj              #+#    #+#             */
/*   Updated: 2021/02/24 15:37:50 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/*
**
** stat ded = 0
** stat eating = 1
** stat sleeping = 2
** stat thinking = 3
**
*/

typedef	struct	s_list
{
	struct	s_list	*next;
	int				philo_pos;
	int				is_ded;
	int				stat;
	int				checker;
	
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int ttd;
	int tte;
	int tts;
	int	tla;
	pthread_t		th;
}				t_list;


#define TTD 1000
#define TTE 300
#define TTS 300
#define N_PHILO 10

pthread_mutex_t lock;

struct timeval g_time_start;

struct s_time_option
{
	int ttd;
	int tte;
	int tts;
} typedef t_time_option;

#endif