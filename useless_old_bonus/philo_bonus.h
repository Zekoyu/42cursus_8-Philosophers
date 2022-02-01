/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:17:34 by mframbou          #+#    #+#             */
/*   Updated: 01-02-2022 16:57 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define USG_STRING "usage: <philo_bonus philosophers_count> <time_to_die> \
<time_to_eat> <time_to_sleep> [minimum_number_of_meals]\n"

# define SEM_FORKS "forks on table"
# define SEM_CANLOCK "can take forks"

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>

# include "libfunctions.h"

typedef struct s_philosopher
{
	pthread_t				self;
	pthread_mutex_t			fork;
	char					fork_available;
	int						number;
	long					last_meal_end;
	int						times_ate;
	struct s_timings		*timings;
	struct s_philosopher	*next;
	char					*someone_died;
	sem_t					*sem;
}	t_philosopher;

typedef struct s_timings
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_die;
	int		eat_target;
}	t_timings;

// Philosophers list
void			add_philo(t_philosopher **philos, t_philosopher *new);
t_philosopher	*create_philo(t_timings *timings, int number, char *philo_died);
t_philosopher	*get_last_lst(t_philosopher *philos);

// Utils
void			init_ms_since_start(void);
long			get_ms_since_start(void);

// Philosophers initialization / destruction
t_philosopher	*create_philos(int count, t_timings *timings, char *philo_died);
void			start_philos(t_philosopher *philos);
void			*free_philos(t_philosopher *first);

// Philo Utils
int				lock_forks(t_philosopher *philo);
void			unlock_forks(t_philosopher *philo);
int				philo_ate_enough(t_philosopher *philo);
int				philo_should_be_dead(t_philosopher *philo);
int				check_death(t_philosopher *philo, long current_ms);
int				forks_are_available(t_philosopher *philo);

// Philo actions
int				philo_eat(t_philosopher *philo);
int				philo_sleep(t_philosopher *philo);
int				philo_think(t_philosopher *philo);

#endif