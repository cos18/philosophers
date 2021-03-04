/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:10:07 by sunpark           #+#    #+#             */
/*   Updated: 2021/03/03 19:23:04 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main_error_handle(char *msg)
{
	printf("[ERR] %s\n", msg);
	return (0);
}

int		main(int argc, char **argv)
{
	int	locate;
	int	argv_num[5];

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
	printf("number_of_philosophers: %d\n", argv_num[0]);
	printf("time_to_die: %d\n", argv_num[1]);
	printf("time_to_eat: %d\n", argv_num[2]);
	printf("time_to_sleep: %d\n", argv_num[3]);
	if (argv_num[4] != STOP_ONLY_DEATH)
		printf("number_of_times_each_philosopher_must_eat: %d\n", argv_num[4]);
}
