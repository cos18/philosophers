/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:30:23 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/08 18:11:42 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		stat_philo_init(t_stat *stat, int locate)
{
	stat->ps[locate].pnum = locate + 1;
	stat->ps[locate].philo_stat = PHILO_SLEEP;
	stat->ps[locate].eat_cnt = 0;
	stat->ps[locate].stat = stat;
	if (pthread_mutex_init(stat->ps[locate].mutex, NULL))
		return (EXIT_FAILURE);
}

void	philo_mutex_free()
{
	int	test;

	test = 10;
}

int		stat_init(t_stat *stat, int *argv_num)
{
	int	locate;

	stat->pcnt = argv_num[0];
	stat->die_time = argv_num[1];
	stat->eat_time = argv_num[2];
	stat->sleep_time = argv_num[3];
	stat->min_eat_pcnt = argv_num[4];
	if ((stat->ps = (t_philo *)malloc(sizeof(t_philo) * stat->pcnt)) == NULL)
		return (EXIT_FAILURE);
	locate = -1;
	while (++locate < stat->pcnt)
	{
		if (stat_philo_init(stat, locate) == EXIT_FAILURE)
		{
			free(stat->ps);
			return (EXIT_FAILURE);
		}
	}
}
