/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 20:51:03 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/10 21:36:56 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p)
{
	pthread_mutex_lock(&(p->stat->fork_mutex[p->pnum]));
	p->philo_stat = PHILO_FORK;
	print_message(p->stat, PHILO_FORK, p->pnum);
	pthread_mutex_lock(&(p->stat->fork_mutex[(p->pnum + 1) % p->stat->pcnt]));
	print_message(p->stat, PHILO_FORK, p->pnum);
	
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(&(p->use_mutex));
	p->philo_stat = PHILO_EAT;
	print_message(p->stat, PHILO_EAT, p->pnum);
	p->starve_dead = get_time() + p->stat->die_time;
	usleep(1000 * p->stat->eat_time);
	pthread_mutex_unlock(&(p->use_mutex));
	pthread_mutex_unlock(&(p->eat_mutex));
}

void	sleep_think(t_philo *p)
{
	print_message(p->stat, PHILO_SLEEP, p->pnum);
	p->philo_stat = PHILO_SLEEP;
	pthread_mutex_unlock(&(p->stat->fork_mutex[p->pnum]));
	pthread_mutex_unlock(&(p->stat->fork_mutex[(p->pnum + 1) % p->stat->pcnt]));
	usleep(1000 * p->stat->sleep_time);
	p->philo_stat = PHILO_THINK;
	print_message(p->stat, PHILO_THINK, p->pnum);
}
