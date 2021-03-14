/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:14:42 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 13:43:04 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		*monitor_eat(void *stat_void)
{
	t_stat		*stat;
	int			*check;
	int			check_cnt;
	int			is_not_end;

	stat = (t_stat *)stat_void;
	if ((check = (int *)malloc(sizeof(int) * stat->pcnt)) == NULL)
		return ((void*)0);
	memset(check, FALSE, sizeof(int) * stat->pcnt);
	check_cnt = 0;
	is_not_end = TRUE;
	while (is_not_end)
		check_eat_cnt(&is_not_end, stat, check, &check_cnt);
	if (print_message(stat, END_EAT, 0))
		return ((void*)0);
	sem_post(stat->die_sem);
	return ((void*)0);
}

static void		*monitor_p(void *philo_void)
{
	t_philo		*p;

	p = (t_philo*)philo_void;
	while (TRUE)
	{
		if (get_time() > p->starve_dead)
		{
			p->philo_stat = PHILO_DIE;
			if (print_message(p->stat, PHILO_DIE, p->pnum))
				return ((void*)0);
			if (sem_post(p->stat->die_sem))
				return ((void*)0);
			return ((void*)0);
		}
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
		if (take_forks(p))
			return ((void*)0);
		if (eat(p))
			return ((void*)0);
		if (sleep_think(p))
			return ((void*)0);
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
	if (pnum % 2 == 0)
		usleep(500 * stat->eat_time);
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
