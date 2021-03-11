/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:32:57 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/11 17:55:08 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int					is_number_char(char c)
{
	return (('0' <= c && c <= '9') ? TRUE : FALSE);
}

int					atoi_strict(char *str)
{
	int				result;

	result = 0;
	while (*str)
	{
		if (is_number_char(*str) == FALSE)
			return (UTIL_ERR);
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return (result);
}

uint64_t			get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void				print_message(t_stat *stat, int status, int philo_num)
{
	static int		end = FALSE;

	pthread_mutex_lock(&(stat->print_mutex));
	if (end == FALSE)
	{
		if (status == END_EAT)
		{
			printf("End eat count by each!\n");
			end = TRUE;
		}
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
			{
				printf("died\n");
				end = TRUE;
			}
		}
	}
	pthread_mutex_unlock(&(stat->print_mutex));
}

sem_t				*sem_init(char *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}
