#include "../include/philo.h"

static t_philo	*philo_create(int id)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->philo_id = id;
	new_philo->meals_nbr = 0;
	new_philo->thread_id = 0;
	new_philo->first_fork = NULL;
	new_philo->second_fork = NULL;
	new_philo->next = NULL;
	new_philo->prev = NULL;
	new_philo->time_until_dead = tv_since_start() + philo()->time_die;
	return (new_philo);
}

static void	ll_philo(t_philo *phil)
{
	t_philo	*cur;

	if (!philo()->philos)
	{
		philo()->philos = phil;
		return ;
	}
	cur = philo()->philos;
	while (cur->next)
		cur = cur->next;
	phil->prev = cur;
	cur->next = phil;
	if (phil->philo_id == philo()->num_philos)
	{
		phil->next = philo()->philos;
		philo()->philos->prev = phil;
	}
}

void	init_philos(void)
{
	t_philo	*new_philo;
	int		i;

	i = 0;
	while (++i <= philo()->num_philos)
	{
		new_philo = philo_create(i);
		ll_philo(new_philo);
	}
	forks_init();
}

static t_forks	*give_fork(void)
{
	t_forks	*new_fork;

	new_fork = malloc(sizeof(t_forks));
	if (!new_fork)
		return (NULL);
	new_fork->is_locked = 0;
	new_fork->mut = malloc(sizeof(pthread_mutex_t));
	if (!new_fork->mut)
		return (NULL);
	if (pthread_mutex_init(new_fork->mut, NULL) != 0)
	{
		printf("Failed to initialize fork mutex>\n");
		return (NULL);
	}
	return (new_fork);
}

void	forks_init(void)
{
	int		i;

	i = -1;
	while (++i < philo()->num_philos)
	{
		if (!philo()->philos->first_fork)
		{
			philo()->philos->first_fork = give_fork();
			if (philo()->num_philos == 1)
				break ;
			philo()->philos->next->second_fork = philo()->philos->first_fork;
		}
		philo()->philos = philo()->philos->next;
	}
}
