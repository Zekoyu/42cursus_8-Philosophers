/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 01-02-2022  by  `-'                        `-'                  */
/*   Updated: 01-02-2022 18:22 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	lock_forks(t_philosopher *philo)
{
	sem_wait(philo->can_lock);
	sem_wait(philo->forks);
	sem_wait(philo->forks);
	sem_post(philo->can_lock);
}

void	unlock_forks(t_philosopher *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}

/*
	Init the first meal at -(time to eat), so that first eat will be set at 0
	and so on (last meal time is set to the time he began to eat)
*/
int	philo_eat(t_philosopher *philo)
{
	long	current_ms;

	lock_forks(philo);
	current_ms = get_ms_since_start();
	if (is_philo_dead(philo, current_ms))
		return (-1);
	printf("%ld %d is eating\n", current_ms, philo->number);
	philo->last_meal_end += philo->timings->time_to_eat;
	if (philo->times_ate == 0)
		philo->last_meal_end = current_ms + philo->timings->time_to_eat;
	philo->times_ate++;
	while (current_ms < philo->last_meal_end)
	{
		if (is_philo_dead(philo, current_ms))
			return (-1);
		usleep(50);
		current_ms = get_ms_since_start();
	}
	unlock_forks(philo);
	return (0);
}

// If last meal was at 0 and philo took 200 to eat, 100 to sleep,
// then we should wait till 300 ms
int	philo_sleep(t_philosopher *philo)
{
	long	current_ms;

	current_ms = get_ms_since_start();
	printf("%ld %d is sleeping\n", current_ms, philo->number);
	while (current_ms < philo->last_meal_end + philo->timings->time_to_sleep)
	{
		if (is_philo_dead(philo, current_ms))
			return (-1);
		usleep(50);
		current_ms = get_ms_since_start();
	}
	return (0);
}

/*
	Only way out is exit

	If philo dies while eating, put back his 2 forks on table
*/
void	*philo_main(t_philosopher *self)
{
	while (1)
	{
		if (self->count == 1)
		{
			while (!is_philo_dead(self, get_ms_since_start()))
				usleep(50);
			exit(EXIT_FAILURE);
		}
		if (philo_eat(self) == -1)
			exit(EXIT_FAILURE);
		if (philo_ate_enough(self))
			exit(EXIT_SUCCESS);
		if (philo_sleep(self) == -1)
			exit(EXIT_FAILURE);
		printf("%ld %d is thinking\n", get_ms_since_start(), self->number);
	}
	exit(EXIT_SUCCESS);
}

