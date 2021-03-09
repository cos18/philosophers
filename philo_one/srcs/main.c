/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:10:07 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/09 21:34:32 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main_error_handle(char *msg)
{
	printf("[ERR] %s\n", msg);
	return (EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	int		locate;
	int		argv_num[5];
	t_stat	stat;

	if (argc < 5 || 6 < argc)
		return (main_error_handle("Wrong Argument count"));
	locate = -1;
	while (++locate < argc - 1)
	{
		if ((argv_num[locate] = atoi_strict(argv[locate + 1])) == UTIL_ERR)
			return (main_error_handle("Argument must be positive integer"));
	}
	if (locate == 4)
		argv_num[locate] = STOP_ONLY_DEATH;
	if (stat_init(&stat, argv_num) == EXIT_FAILURE)
		return (main_error_handle("Error duruing malloc"));
	if (run_thread(&stat) == EXIT_FAILURE)
		main_error_handle("Error during running thread");
	stat_free_destroy(&stat);
}
