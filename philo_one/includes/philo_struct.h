/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:20:31 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/11 14:59:37 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_THINK 0
# define PHILO_FORK 1
# define PHILO_EAT 2
# define PHILO_SLEEP 3
# define PHILO_DIE 4
# define END_EAT 5
# define DROP_FORK 6

struct s_stat;

typedef struct		s_philo
{
	int				pnum;
	int				philo_stat;
	int				eat_cnt;
	uint64_t		starve_dead;
	pthread_mutex_t	use_mutex;
	pthread_mutex_t eat_mutex;
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
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t die_mutex;
	pthread_mutex_t print_mutex;
	t_philo			*ps;
}					t_stat;

int					stat_init(t_stat *stat, int *argv_num);
void				stat_free_destroy(t_stat *stat);

#endif
