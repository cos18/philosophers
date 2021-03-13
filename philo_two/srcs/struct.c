/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:30:23 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/13 19:56:19 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	stat_philo_close(t_stat *stat, int locate)
{
	char	*name;
	int		pnum;

	pnum = 0;
	while (pnum++ < locate)
	{
		name = make_sem_name(SEM_USE_NAME, pnum);
		sem_unlink(name);
		free(name);
		name = make_sem_name(SEM_EAT_NAME, pnum);
		sem_unlink(name);
		free(name);
	}
	free(stat->ps);
	return (EXIT_FAILURE);
}

static int	stat_philo_init(t_stat *stat, int locate)
{
	char	*name;

	stat->ps[locate].pnum = locate + 1;
	stat->ps[locate].philo_stat = PHILO_THINK;
	stat->ps[locate].eat_cnt = 0;
	stat->ps[locate].stat = stat;
	stat->ps[locate].use_sem = NULL;
	stat->ps[locate].eat_sem = NULL;
	if ((name = make_sem_name(SEM_USE_NAME, locate + 1)) == NULL)
		return (EXIT_FAILURE);
	stat->ps[locate].use_sem = sem_custom_init(name, 1);
	free(name);
	if (stat->ps[locate].use_sem == SEM_FAILED)
		return (EXIT_FAILURE);
	if ((name = make_sem_name(SEM_EAT_NAME, locate + 1)) != NULL)
	{
		stat->ps[locate].eat_sem = sem_custom_init(name, 1);
		free(name);
		if (stat->ps[locate].eat_sem != SEM_FAILED)
			return (EXIT_SUCCESS);
	}
	printf("THIS?\n");
	sem_close(stat->ps[locate].use_sem);
	stat->ps[locate].use_sem = NULL;
	return (EXIT_FAILURE);
}

int			stat_free_close(t_stat *stat)
{
	if (stat->ps)
		stat_philo_close(stat, stat->pcnt);
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
	{
		if (stat_philo_init(stat, locate) == EXIT_FAILURE)
			return (stat_philo_close(stat, locate));
	}
	if ((stat->print_sem = sem_custom_init(SEM_PRINT_NAME, 1)) == SEM_FAILED || 
(stat->fork_sem = sem_custom_init(SEM_FORK_NAME, stat->pcnt)) == SEM_FAILED ||
	(stat->die_sem = sem_custom_init(SEM_DIE_NAME, 1)) == SEM_FAILED)
		return (stat_free_close(stat));
	sem_wait(stat->die_sem);
	return (EXIT_SUCCESS);
}
