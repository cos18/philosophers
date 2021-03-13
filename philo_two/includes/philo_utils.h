/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:12:31 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/13 19:08:00 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include "philo_struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define TRUE 1
# define FALSE 0
# define UTIL_ERR -1
# define SEM_SUCCESS 0
# define SEM_FAIL -1

int			ft_strlen(char *str);
int			atoi_strict(char *str);
uint64_t	get_time(void);
int			print_message(t_stat *stat, int status, int philo_num);

# define SEM_USE_NAME "SEM_USE_"
# define SEM_EAT_NAME "SEM_EAT_"
# define SEM_PRINT_NAME "SEM_PRINT"
# define SEM_FORK_NAME "SEM_FORK"
# define SEM_DIE_NAME "SEM_DIE"

sem_t		*sem_custom_init(char *name, int value);
char		*make_sem_name(char *sem_stat_name, int philo_num);

#endif
