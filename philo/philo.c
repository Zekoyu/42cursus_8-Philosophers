/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:56:11 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/17 14:54:46 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char *argv[], t_timings *timings)
{
	int	philo_count;

	philo_count = 0;
	timings->time_to_die = 0;
	timings->time_to_eat = 0;
	timings->time_to_sleep = 0;
	timings->eat_target = 0;
	argc--;
	argv++;
	if (argc < 4 || argc > 5)
		return (-1);
	philo_count = (int)ft_atol(argv[0]);
	timings->time_to_die = ft_atol(argv[1]);
	timings->time_to_eat = ft_atol(argv[2]);
	timings->time_to_sleep = ft_atol(argv[3]);
	if (argc == 5)
		timings->eat_target = ft_atol(argv[4]);
	if (timings->eat_target == -1 || timings->time_to_eat == -1 \
	|| timings->time_to_sleep == -1 || timings->eat_target == -1)
		return (-1);
	return (philo_count);
}

/*
 Each philosopher should try to take the fork of the one on his left
 ONLY IF his fork is available
 
 Which means first only 1 out of 2 will eat, then put back the fork,
 and then the other ones will eat

 If one dies, only set the "someone_died" variable to a, since it's a pointer
 It will be retrieved in the main and the simulation can end properly
*/
int	main(int argc, char *argv[])
{
	t_timings		timings;
	t_philosopher	*philos;
	t_philosopher	*current;
	int				philos_count;
	char			someone_died;

	philos_count = parse_args(argc, argv, &timings);
	if (philos_count <= 0)
	{
		write(1, USG_STRING, 105);
		return (EXIT_FAILURE);
	}
	philos = create_philos(philos_count, &timings, &someone_died);
	init_ms_since_start();
	start_philos(philos);
	current = philos;
	while (philos_count > 0)
	{
		pthread_join(current->self, NULL);
		current = current->next;
		philos_count--;
	}
	free_philos(philos);
	return (EXIT_SUCCESS);
}
