/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 01-02-2022  by  `-'                        `-'                  */
/*   Updated: 01-02-2022 18:24 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_ate_enough(t_philosopher *philo)
{
	if (philo->timings->eat_target <= 0)
		return (0);
	return (philo->times_ate >= philo->timings->eat_target);
}

/*
	Count from the beggining of the last meal not the end
*/
static int	philo_should_be_dead(t_philosopher *philo)
{
	if (philo->times_ate != 0)
		return (get_ms_since_start() - \
		(philo->last_meal_end - philo->timings->time_to_eat) \
		> philo->timings->time_to_die);
	else
		return (get_ms_since_start() > philo->timings->time_to_die);
}

int	is_philo_dead(t_philosopher *philo, long current_ms)
{
	if (philo_should_be_dead(philo))
	{
		unlock_forks(philo);
		fprintf(stdout, "%ld %d died\n", current_ms, philo->number);
		return (1);
	}
	return (0);
}
