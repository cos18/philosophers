/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:20:31 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/03 19:31:56 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

struct s_status;

typedef struct	s_philo
{
	int			pnum;
	int			status;
	struct s_status	status;
}				t_philo;

typedef struct	s_status
{
	int			pcnt;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			min_eat_pcnt;
	t_philo		*philos;
}				t_status;

#endif
