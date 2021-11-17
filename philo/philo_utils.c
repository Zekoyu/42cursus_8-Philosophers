/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:29:35 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/17 16:03:24 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->fork);
	if (philo->next != philo)
		pthread_mutex_unlock(&philo->next->fork);
	philo->fork_available = 1;
	philo->next->fork_available = 1;
}

int	philo_ate_enough(t_philosopher *philo)
{
	if (philo->timings->eat_target <= 0)
		return (0);
	return (philo->times_ate >= philo->timings->eat_target);
}

// Count from the beggining of the last meal not the end
int	philo_should_be_dead(t_philosopher *philo)
{
	if (philo->times_ate != 0)
		return (get_ms_since_start() - \
		(philo->last_meal_end - philo->timings->time_to_eat) \
		> philo->timings->time_to_die);
	else
		return (get_ms_since_start() > philo->timings->time_to_die);
}

int	lock_forks(t_philosopher *philo)
{
	long	ms_since_start;

	philo->fork_available = 0;
	philo->next->fork_available = 0;
	if (philo->next != philo)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		ms_since_start = get_ms_since_start();
		printf("%ld %d has taken a fork\n%ld %d has taken a fork\n", \
		ms_since_start, philo->number, ms_since_start, philo->number);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		ms_since_start = get_ms_since_start();
		printf("%ld %d has taken a fork\n", ms_since_start, philo->number);
		return (0);
	}
}

int	check_death(t_philosopher *philo, long current_ms)
{
	if (philo_should_be_dead(philo))
	{
		unlock_forks(philo);
		printf("%ld %d died\n", current_ms, philo->number);
		*(philo->someone_died) = 1;
		return (0);
	}
	else if (*philo->someone_died)
	{
		unlock_forks(philo);
		return (0);
	}
	return (1);
}
