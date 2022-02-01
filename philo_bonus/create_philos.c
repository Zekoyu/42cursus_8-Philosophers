/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 01-02-2022  by  `-'                        `-'                  */
/*   Updated: 01-02-2022 18:20 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(t_philosopher *philo, sem_t *can_lock, sem_t *forks, \
					t_timings *timings)
{
	philo->can_lock = can_lock;
	philo->forks = forks;
	philo->last_meal_end = 0;
	philo->times_ate = 0;
	philo->timings = timings;
}

static void	*free_pids_ret_null(pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
		kill(pids[i++], SIGTERM);
	free(pids);
	return (NULL);
}

/*
	Returns the list of philo PIDs, ending with -1

	When killing on error, start from i - 1

	If we reach after else if, it means we are in parent
*/
pid_t	*create_philos(int philos_count, sem_t *can_lock, sem_t *forks, \
						t_timings timings)
{
	pid_t			*pids;
	t_philosopher	self;
	int				i;

	pids = malloc(sizeof(pid_t) * (philos_count + 1));
	if (!pids)
		return (NULL);
	pids[philos_count] = -1;
	i = -1;
	while (++i < philos_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (free_pids_ret_null(pids, i));
		else if (pids[i] == 0)
		{
			free(pids);
			self.number = i + 1;
			self.count = philos_count;
			init_philo(&self, can_lock, forks, &timings);
			philo_main(&self);
		}
	}
	return (pids);
}
