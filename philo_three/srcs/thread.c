/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:32:35 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 16:12:00 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*monitor_eat(void *stat_void)
{
	t_stat	*stat;
	int		cnt;

	stat = (t_stat *)stat_void;
	cnt = 0;
	while (cnt++ < stat->pcnt)
		sem_wait(stat->fin_sem);
	if (print_message(stat, END_EAT, 0))
		return ((void*)0);
	sem_post(stat->die_sem);
	return ((void*)0);
}

void		*monitor_p(void *philo_void)
{
	t_philo	*p;

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
