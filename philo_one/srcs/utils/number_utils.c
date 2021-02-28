/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:32:57 by sunpark           #+#    #+#             */
/*   Updated: 2021/02/28 18:41:26 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_number_char(char c)
{
	return (('0' <= c && c <= '9') ? TRUE : FALSE);
}

int		atoi_strict(char *str)
{
	int	result;

	result = 0;
	while (*str)
	{
		if (is_number_char(*str) == FALSE)
			return (UTIL_ERR);
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return (result);
}
