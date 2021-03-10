/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:30:23 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/10 21:00:02 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stat_philo_init(t_stat *stat, int locate)
{
	stat->ps[locate].pnum = locate + 1;
	stat->ps[locate].philo_stat = PHILO_THINK;
	stat->ps[locate].eat_cnt = 0;
	stat->ps[locate].stat = stat;
	pthread_mutex_init(&(stat->ps[locate].use_mutex), NULL);
	pthread_mutex_init(&(stat->ps[locate].eat_mutex), NULL);
}

int			stat_init(t_stat *stat, int *argv_num)
{
	int		locate;

	stat->pcnt = argv_num[0];
	stat->die_time = argv_num[1];
	stat->eat_time = argv_num[2];
	stat->sleep_time = argv_num[3];
	stat->min_eat_pcnt = argv_num[4];
	if ((stat->ps = (t_philo *)malloc(sizeof(t_philo) * stat->pcnt)) == NULL)
		return (EXIT_FAILURE);
	if ((stat->fork_mutex =
	(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * stat->pcnt)) == NULL)
	{
		free(stat->ps);
		return (EXIT_FAILURE);
	}
	locate = -1;
	while (++locate < stat->pcnt)
	{
		stat_philo_init(stat, locate);
		pthread_mutex_init(stat->fork_mutex + locate, NULL);
	}
	pthread_mutex_init(&(stat->print_mutex), NULL);
	pthread_mutex_init(&(stat->die_mutex), NULL);
	pthread_mutex_lock(&(stat->die_mutex));
	return (EXIT_SUCCESS);
}

void		stat_free_destroy(t_stat *stat)
{
	int		locate;

	locate = -1;
	while (++locate < stat->pcnt)
	{
		pthread_mutex_destroy(&(stat->ps[locate].use_mutex));
		pthread_mutex_destroy(&(stat->ps[locate].eat_mutex));
		pthread_mutex_destroy(stat->fork_mutex + locate);
	}
	free(stat->ps);
	free(stat->fork_mutex);
}
