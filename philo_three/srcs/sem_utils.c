/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:08:21 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/13 18:39:11 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t		*sem_custom_init(char *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char		*make_sem_name(char *sem_stat_name, int philo_num)
{
	int		locate;
	char	*result;

	result = (char *)malloc(sizeof(int) * (10 + ft_strlen(sem_stat_name)));
	if (result == NULL)
		return (NULL);
	locate = 0;
	while (*sem_stat_name)
		result[locate++] = *(sem_stat_name++);
	while (philo_num)
	{
		result[locate++] = philo_num % 10 + '0';
		philo_num /= 10;
	}
	result[locate] = '\0';
	return (result);
}
