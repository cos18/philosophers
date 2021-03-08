/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:20:31 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/08 17:35:28 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>
# include "philo_utils.h"

# define PHILO_THINK 0
# define PHILO_FORK 1
# define PHILO_EAT 2
# define PHILO_SLEEP 3
# define PHILO_DIE 4

struct				s_stat;

typedef struct		s_philo
{
	int				pnum;
	int				philo_stat;
	int				eat_cnt;
	pthread_mutex_t	*mutex;
	struct s_stat	*stat;
}					t_philo;

typedef struct		s_stat
{
	int				pcnt;
	uint64_t		die_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				min_eat_pcnt;
	uint64_t		start_t;
	t_philo			*ps;
}					t_stat;

#endif
