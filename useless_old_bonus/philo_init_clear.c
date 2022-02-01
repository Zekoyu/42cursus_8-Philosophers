/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:41:09 by mframbou          #+#    #+#             */
/*   Updated: 01-02-2022 16:47 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*free_philos(t_philosopher *first)
{
	t_philosopher	*curr;
	t_philosopher	*next;

	curr = first;
	while (curr && curr != first)
	{
		next = curr->next;
		pthread_mutex_destroy(&curr->fork);
		free(curr);
		curr = next;
	}
	return (NULL);
}

t_philosopher	*create_philos(int count, t_timings *timings, char *philo_died)
{
	t_philosopher	*first;
	t_philosopher	*new;
	t_philosopher	*last;
	int				i;

	i = 1;
	*philo_died = 0;
	first = NULL;
	new = NULL;
	last = NULL;
	while (i <= count)
	{
		new = create_philo(timings, i, philo_died);
		if (!new)
			return (free_philos(first));
		if (i == 1)
			first = new;
		add_philo(&first, new);
		i++;
	}
	last = new;
	last->next = first;
	return (first);
}

void	*philo_main(void *arg)
{
	t_philosopher	*self;

	self = (t_philosopher *)arg;
	while (1)
	{
		if (philo_eat(self) == -1)
			exit (EXIT_FAILURE);
		if (philo_ate_enough(self))
			exit (EXIT_SUCCESS);
		if (philo_sleep(self) == -1)
			exit (EXIT_FAILURE);
		if (philo_think(self) == -1)
			exit (EXIT_FAILURE);
	}
}

void	start_philos(t_philosopher *philos)
{
	t_philosopher	*current;
	pthread_t		philo_thread;

	current = philos;
	pthread_create(&philo_thread, NULL, &philo_main, current);
	current->self = philo_thread;
	current = current->next;
	while (current && current != philos)
	{
		pthread_create(&philo_thread, NULL, &philo_main, current);
		current->self = philo_thread;
		current = current->next;
		usleep(25);
	}
}
