/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:56:11 by mframbou          #+#    #+#             */
/*   Updated: 03-02-2022 16:13 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

/*
	Returns an NULL and prints error if sem couldn't be created
*/
sem_t	*create_sem(char *name, int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
	if (sem == SEM_FAILED)
	{
		if (sem_unlink(name) == -1)
		{
			ft_putstr_fd("Couln't create ", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putstr_fd(" semaphore, another one is \
			already opened and cannot be closed.\n", STDERR_FILENO);
			return (NULL);
		}
		else
		{
			sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
			if (sem == SEM_FAILED)
			{
				ft_putstr_fd("Couln't create ", STDERR_FILENO);
				ft_putstr_fd(name, STDERR_FILENO);
				ft_putstr_fd(" semaphore, another one was opened, then unlinked \
				but new one cannot be created.\n", STDERR_FILENO);
				return (NULL);
			}
		}
	}
	return (sem);
}

static int	start_and_wait_philos(int philos_count, sem_t *sem_wants_to_lock, \
									sem_t *sem_forks, t_timings timings)
{
	pid_t	*pids;
	int		return_val;
	int		i;

	init_ms_since_start();
	pids = create_philos(philos_count, sem_wants_to_lock, sem_forks, timings);
	if (!pids)
		ft_putstr_fd("Couldn't malloc or start the philos", STDERR_FILENO);
	if (!pids)
		return (EXIT_FAILURE);
	while (philos_count > 0)
	{
		return_val = 0;
		waitpid(-1, &return_val, 0);
		if (WIFEXITED(return_val) && WEXITSTATUS(return_val) == EXIT_FAILURE)
		{
			i = -1;
			while (pids[++i] != -1)
				kill(pids[i], SIGTERM);
			free(pids);
			return (EXIT_FAILURE);
		}
		philos_count--;
	}
	return (EXIT_SUCCESS);
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
	int				philos_count;
	sem_t			*sem_forks;
	sem_t			*sem_wants_to_lock;

	philos_count = parse_args(argc, argv, &timings);
	if (philos_count <= 0)
	{
		write(1, USG_STRING, 111);
		return (EXIT_FAILURE);
	}
	sem_forks = create_sem(SEM_FORKS, philos_count);
	sem_wants_to_lock = create_sem(SEM_CANLOCK, 1);
	if (!sem_forks || !sem_wants_to_lock)
	{
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_CANLOCK);
	}
	return (start_and_wait_philos(philos_count, sem_wants_to_lock, sem_forks, \
									timings));
}
