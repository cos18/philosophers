/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:30:23 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 15:58:19 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stat_philo_init(t_stat *stat, int locate)
{
	stat->ps[locate].pnum = locate + 1;
	stat->ps[locate].philo_stat = PHILO_THINK;
	stat->ps[locate].eat_cnt = 0;
	stat->ps[locate].stat = stat;
}

int			stat_free_close(t_stat *stat)
{
	if (stat->ps)
		free(stat->ps);
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_DIE_NAME);
	sem_unlink(SEM_PRINT_NAME);
	return (EXIT_FAILURE);
}

int			stat_init(t_stat *stat, int *argv_num)
{
	int		locate;

	stat->pcnt = argv_num[0];
	stat->die_time = argv_num[1];
	stat->eat_time = argv_num[2];
	stat->sleep_time = argv_num[3];
	stat->min_eat_pcnt = argv_num[4];
	stat->print_sem = NULL;
	stat->fork_sem = NULL;
	stat->die_sem = NULL;
	if ((stat->ps = (t_philo *)malloc(sizeof(t_philo) * stat->pcnt)) == NULL)
		return (EXIT_FAILURE);
	locate = -1;
	while (++locate < stat->pcnt)
		stat_philo_init(stat, locate);
	if ((stat->print_sem = sem_custom_init(SEM_PRINT_NAME, 1)) == SEM_FAILED ||
	(stat->fork_sem = sem_custom_init(SEM_FORK_NAME, stat->pcnt))
		== SEM_FAILED ||
	(stat->die_sem = sem_custom_init(SEM_DIE_NAME, 0)) == SEM_FAILED)
		return (stat_free_close(stat));
	return (EXIT_SUCCESS);
}
