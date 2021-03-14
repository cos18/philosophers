/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 13:42:55 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 13:43:19 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eat_cnt(int *is_not_end, t_stat *stat, int *check, int *check_cnt)
{
	int	pnum;

	pnum = -1;
	while (++pnum < stat->pcnt)
	{
		if (check[pnum])
			continue ;
		if (stat->ps[pnum].eat_cnt >= stat->min_eat_pcnt)
		{
			check[pnum] = TRUE;
			*check_cnt = *check_cnt + 1;
			if (*check_cnt == stat->pcnt)
			{
				*is_not_end = FALSE;
				break ;
			}
		}
	}
}
