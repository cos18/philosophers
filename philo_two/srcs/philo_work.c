/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 20:51:03 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/13 20:44:32 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *p)
{
	if (sem_wait(p->stat->fork_sem))
		return (SEM_FAIL);
	p->philo_stat = PHILO_FORK;
	if (print_message(p->stat, PHILO_FORK, p->pnum))
		return (SEM_FAIL);
	if (sem_wait(p->stat->fork_sem))
		return (SEM_FAIL);
	return (print_message(p->stat, PHILO_FORK, p->pnum) ? SEM_FAIL
														: SEM_SUCCESS);
}

int	eat(t_philo *p)
{
	p->philo_stat = PHILO_EAT;
	if (print_message(p->stat, PHILO_EAT, p->pnum))
		return (SEM_FAIL);
	p->starve_dead = get_time() + p->stat->die_time;
	usleep(1000 * p->stat->eat_time);
	(p->eat_cnt)++;
	return (SEM_SUCCESS);
}

int	sleep_think(t_philo *p)
{
	if (print_message(p->stat, PHILO_SLEEP, p->pnum))
		return (SEM_FAIL);
	if (sem_post(p->stat->fork_sem))
		return (SEM_FAIL);
	if (sem_post(p->stat->fork_sem))
		return (SEM_FAIL);
	p->philo_stat = PHILO_SLEEP;
	usleep(1000 * p->stat->sleep_time);
	p->philo_stat = PHILO_THINK;
	return (print_message(p->stat, PHILO_THINK, p->pnum) ? SEM_FAIL
														: SEM_SUCCESS);
}
