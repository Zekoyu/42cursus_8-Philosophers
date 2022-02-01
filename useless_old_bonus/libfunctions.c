/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfunctions_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:56:48 by mframbou          #+#    #+#             */
/*   Updated: 01-02-2022 13:22 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (res);
}
