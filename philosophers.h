/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:50:54 by mmaj              #+#    #+#             */
/*   Updated: 2021/02/23 16:58:15 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef	struct	s_list
{
	struct	s_list	*next;
	int				philo_pos;
	int				is_ded;
	
	int ttd;
	int tte;
	int tts;
	pthread_t		th;
}				t_list;


#define TTD 500000
#define TTE 200000
#define TTS 500000

pthread_mutex_t lock;

struct timeval g_time_start;

struct s_time_option
{
	int ttd;
	int tte;
	int tts;
} typedef t_time_option;

#endif