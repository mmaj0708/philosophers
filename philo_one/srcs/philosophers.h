/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaj <mmaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:50:54 by mmaj              #+#    #+#             */
/*   Updated: 2021/03/02 11:28:15 by mmaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

# define TTD 810
# define TTE 200
# define TTS 400
# define N_PHILO 12
# define FAILURE -1
# define FALSE 0
# define TRUE 1

/*
** stat ded = 0
** stat eating = 1
** stat sleeping = 2
** stat thinking = 3
*/

typedef	struct	s_list
{
	struct s_list	*next;
	int				philo_pos;
	int				is_ded;
	int				stat;
	int				checker;

	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	*mut_print;
	int				ttd;
	int				tte;
	int				tts;
	int				tla;
	int				n_philo;
	int				n_meal;
	int				alive;
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

struct timeval	g_time_start;
int				g_philo_ate;
int				g_eatordeath;

void			*philo_life(void *lst);
int				affect_fork(int n_philo, t_list *list);
long int		gettime(struct timeval start);
int				death_checker(t_list *list, int n_philo);
t_param			*parsing(int ac, char **av);
int				launch_philo(t_list	*list, int n_philo);
t_list			*create_philo(t_param *p, t_list *l, int n_philo, int n_meal);
void			make_list_loop(t_list *list);

int				ft_isdigit(int c);
int				ft_atoi(char *str);

int				get_fork(t_list *list);
int				get_eat(t_list *list);
int				get_sleep(t_list *list);
int				get_think(t_list *list);

void			check_list_elmt(t_list *list, int n_philo);
void			check_param(t_param *param);
void			check_fork_assignation(t_list *list, int n_philo);
void			check_list(t_list *list);

#endif
