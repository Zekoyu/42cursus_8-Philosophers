/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:31:24 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/16 14:21:56 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*create_philo(t_timings *timings, int number, char *philo_died)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) malloc(sizeof(t_philosopher));
	if (philo)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo->last_meal_end = 0;
		philo->someone_died = philo_died;
		philo->number = number;
		philo->timings = timings;
		philo->times_ate = 0;
		philo->next = NULL;
	}
	return (philo);
}

t_philosopher	*get_last_lst(t_philosopher *first)
{
	if (first != NULL)
		while (first->next)
			first = first->next;
	return (first);
}

void	add_philo(t_philosopher **philos, t_philosopher *new)
{
	t_philosopher	*last;

	if (!philos || *philos == new)
		return ;
	last = get_last_lst(*philos);
	if (last)
		last->next = new;
	else
		*philos = new;
}
