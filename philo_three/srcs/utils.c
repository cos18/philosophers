/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:32:57 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 17:22:55 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					ft_strlen(char *str)
{
	return (*str ? 1 + ft_strlen(str + 1) : 0);
}

int					atoi_strict(char *str)
{
	int				result;

	result = 0;
	while (*str)
	{
		if ('0' > *str || *str > '9')
			return (UTIL_ERR);
		result *= 10;
		result += (*str - '0');
		str++;
	}
	if (result == 0)
		return (UTIL_ERR);
	return (result);
}

uint64_t			get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

static void			print_message_bt_status(t_stat *stat, int status,
											int philo_num)
{
	if (status == END_EAT)
		printf("End eat count by each!\n");
	else
	{
		printf("%d %d ", (int)(get_time() - stat->start_t), philo_num);
		if (status == PHILO_THINK)
			printf("is thinking\n");
		else if (status == PHILO_FORK)
			printf("has taken a fork\n");
		else if (status == PHILO_EAT)
			printf("is eating\n");
		else if (status == PHILO_SLEEP)
			printf("is sleeping\n");
		else
			printf("died\n");
	}
}

int					print_message(t_stat *stat, int status, int philo_num)
{
	static int		end = FALSE;
	int				result;

	if (sem_wait(stat->print_sem))
		return (SEM_FAIL);
	result = SEM_FAIL;
	if (end == FALSE)
	{
		print_message_bt_status(stat, status, philo_num);
		if (status == END_EAT || status == PHILO_DIE)
			end = TRUE;
		result = SEM_SUCCESS;
	}
	if (end == FALSE)
	{
		if (sem_post(stat->print_sem))
			return (SEM_FAIL);
	}
	return (result);
}
