/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:12:31 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 17:02:03 by sunpark          ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0
# define UTIL_ERR -1

int			is_number_char(char c);
int			atoi_strict(char *str);
uint64_t	get_time(void);
void		print_message(t_stat *stat, int status, int philo_num);
void		check_eat_cnt(int *is_not_end, t_stat *stat, int *check,
							int *check_cnt);

#endif
