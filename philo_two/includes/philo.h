/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:11:46 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/13 18:42:49 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <semaphore.h>
# include "philo_utils.h"
# include "philo_struct.h"

# define STOP_ONLY_DEATH -1

int		run_thread(t_stat *stat);

int		take_forks(t_philo *p);
int		eat(t_philo *p);
int		sleep_think(t_philo *p);

#endif
