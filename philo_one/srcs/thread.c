/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:14:42 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/10 21:39:39 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		*monitor_eat(void *stat_void)
{
	t_stat		*stat;
	int			check;
	int			pnum;

	stat = (t_stat *)stat_void;
	check = -1;
	while (++check < stat->min_eat_pcnt)
	{
		pnum = 0;
		while (pnum < stat->pcnt)
		{
			if (stat->ps[pnum].philo_stat == PHILO_DIE)
				return ((void*)0);
			pthread_mutex_lock(&(stat->ps[pnum].eat_mutex));
			if (stat->ps[pnum++].philo_stat == PHILO_DIE)
				return ((void*)0);
		}
	}
	print_message(stat, END_EAT, 0);
	pthread_mutex_unlock(&(stat->die_mutex));
	return ((void*)0);
}

static void		*monitor_p(void *philo_void)
{
	t_philo		*p;

	p = (t_philo*)philo_void;
	while (TRUE)
	{
		pthread_mutex_lock(&(p->use_mutex));
		if (get_time() > p->starve_dead)
		{
			p->philo_stat = PHILO_DIE;
			print_message(p->stat, PHILO_DIE, p->pnum);
			pthread_mutex_unlock(&(p->stat->die_mutex));
			pthread_mutex_unlock(&(p->use_mutex));
			return ((void*)0);
		}
		pthread_mutex_unlock(&(p->use_mutex));
		usleep(1000);
	}
}

static void		*philo_work(void *philo_void)
{
	pthread_t	tid;
	t_philo		*p;

	p = (t_philo*)philo_void;
	p->starve_dead = get_time() + p->stat->die_time;
	if (pthread_create(&tid, NULL, &monitor_p, philo_void) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(p);
		eat(p);
		sleep_think(p);
	}
	return ((void*)0);
}

static int		run_philo(t_stat *stat, int pnum)
{
	void		*p;
	pthread_t	tid;

	while (pnum < stat->pcnt)
	{
		p = (void*)(&(stat->ps[pnum]));
		if (pthread_create(&tid, NULL, &philo_work, p) != 0)
			return (EXIT_FAILURE);
		pthread_detach(tid);
		pnum += 2;
	}
	usleep(100);
	return (EXIT_SUCCESS);
}

int				run_thread(t_stat *stat)
{
	pthread_t	tid;

	stat->start_t = get_time();
	if (stat->min_eat_pcnt != STOP_ONLY_DEATH)
	{
		if (pthread_create(&tid, NULL, &monitor_eat, (void*)stat) != 0)
			return (EXIT_FAILURE);
		pthread_detach(tid);
	}
	if (run_philo(stat, 0) == EXIT_FAILURE ||
		run_philo(stat, 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
