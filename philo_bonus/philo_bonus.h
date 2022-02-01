/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:17:34 by mframbou          #+#    #+#             */
/*   Updated: 01-02-2022 18:20 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define USG_STRING "usage: philo_bonus <philosophers_count> <time_to_die> \
<time_to_eat> <time_to_sleep> [minimum_number_of_meals]\n"

# define SEM_FORKS "forks on table"
# define SEM_CANLOCK "can take forks"

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philosopher
{
	int					number;
	long				last_meal_end;
	int					times_ate;
	struct s_timings	*timings;
	sem_t				*forks;
	sem_t				*can_lock;
	int					count;
}	t_philosopher;

typedef struct s_timings
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_die;
	int		eat_target;
}	t_timings;

// Utils
void	init_ms_since_start(void);
long	get_ms_since_start(void);

// Philosophers initialization / destruction
pid_t	*create_philos(int count, sem_t *can_lock, sem_t *forks, t_timings tim);

// Philo Utils
int		philo_ate_enough(t_philosopher *philo);
int		is_philo_dead(t_philosopher *philo, long current_ms);
void	unlock_forks(t_philosopher *philo);

// Philo actions
void	*philo_main(t_philosopher *self);
int		philo_eat(t_philosopher *philo);
int		philo_sleep(t_philosopher *philo);
int		philo_think(t_philosopher *philo);

// Utils
long	ft_atol(char *str);
void	ft_putchar(char c);
void	ft_putnbr(long nb);;
long	get_ms_since_start(void);
void	init_ms_since_start(void);

#endif