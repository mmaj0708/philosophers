/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:50:54 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/01 11:16:31 by mmaj             ###   ########.fr       */
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
	int	n_philo;
	int	n_meal;
	int alive;
	pthread_t		th;
}				t_list;

typedef	struct	s_param
{
	int ttd;
	int tte;
	int tts;
	int	n_philo;
	int	n_meal;
}				t_param;


#define TTD 810
#define TTE 200
#define TTS 400
#define N_PHILO 12
#define FAILURE -1
#define FALSE 0
#define TRUE 1

pthread_mutex_t lock;

struct timeval g_time_start;
int				g_philo_ate;
int				g_eatordeath;

struct s_time_option
{
	int ttd;
	int tte;
	int tts;
} typedef t_time_option;

void	*philo_life(void *lst);
long int	gettime(struct timeval start);
int	death_checker(t_list *list, int n_philo);

#endif