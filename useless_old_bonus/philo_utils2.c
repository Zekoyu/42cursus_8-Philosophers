/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:49:56 by mframbou          #+#    #+#             */
/*   Updated: 01-02-2022 13:22 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	forks_are_available(t_philosopher *philo)
{
	return (philo->fork_available && philo->next->fork_available);
}
