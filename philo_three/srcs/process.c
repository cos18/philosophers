/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:14:42 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 16:26:11 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		philo_work(t_philo *p)
{
	pthread_t	tid;

	p->starve_dead = get_time() + p->stat->die_time;
	if (pthread_create(&tid, NULL, &monitor_p, (void *)p) != 0)
		return (EXIT_FAILURE);
	pthread_detach(tid);
	while (TRUE)
	{
		if (take_forks(p))
			return (EXIT_FAILURE);
		if (eat(p))
			return (EXIT_FAILURE);
		if (drop_forks(p))
			return (EXIT_FAILURE);
		if (p->eat_cnt == p->stat->min_eat_pcnt)
			break ;
		if (sleep_think(p))
			return (EXIT_FAILURE);
	}
	sem_post(p->stat->fin_sem);
	return (EXIT_SUCCESS);
}

static int		run_philo(t_stat *stat, int pnum)
{
	t_philo		*p;

	while (pnum < stat->pcnt)
	{
		p = &(stat->ps[pnum]);
		if ((p->pid = fork()) < 0)
			return (EXIT_FAILURE);
		else if (p->pid == 0)
			exit(philo_work(p));
		pnum += 2;
	}
	if (pnum % 2 == 0)
		usleep(500 * stat->eat_time);
	return (EXIT_SUCCESS);
}

int				run_process(t_stat *stat)
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
