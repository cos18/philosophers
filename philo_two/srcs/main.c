/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:10:07 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/14 17:25:12 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	main_error_handle(t_stat *stat, char *msg)
{
	printf("[ERR] %s\n", msg);
	if (stat)
		stat_free_close(stat);
	return (EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	int		locate;
	int		argv_num[5];
	t_stat	stat;

	if (argc < 5 || 6 < argc)
		return (main_error_handle(NULL, "Wrong Argument count"));
	locate = -1;
	while (++locate < argc - 1)
	{
		if ((argv_num[locate] = atoi_strict(argv[locate + 1])) == UTIL_ERR)
			return (main_error_handle(NULL,
					"Argument must be positive integer"));
	}
	if (locate == 4)
		argv_num[locate] = STOP_ONLY_DEATH;
	if (argv_num[0] == 1)
		return (main_error_handle(NULL, "Minimum Philosopher is two"));
	if (stat_init(&stat, argv_num) == EXIT_FAILURE)
		return (main_error_handle(NULL, "Error duruing malloc"));
	if (run_thread(&stat) == EXIT_FAILURE)
		main_error_handle(&stat, "Error during running thread");
	sem_wait(stat.die_sem);
	sem_post(stat.die_sem);
	stat_free_close(&stat);
}
