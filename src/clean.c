#include "../include/philo.h"

static void forks()
{
	int		i;

	i = 0;
	if (!philo()->philos)
		return;
	while (++i <= philo()->philos->philo_id)
	{
		if (philo()->philos->first_fork->mut)
		{
			pthread_mutex_destroy(philo()->philos->first_fork->mut);
			free(philo()->philos->first_fork->mut);
			free(philo()->philos->first_fork);
			philo()->philos->first_fork = NULL;
			if (philo()->num_philos == 1)
				return ;
			philo()->philos->next->second_fork = NULL;
		}
		philo()->philos = philo()->philos->next;
	}
}

static void philos()
{
	t_philo	*temp;

	if (!philo()->philos)
		return;
	if (philo()->num_philos == 1)
	{
		free(philo()->philos);
		return ;
	}
	philo()->philos->prev->next = NULL;
	while (philo()->philos)
	{
		temp = philo()->philos;
		philo()->philos = philo()->philos->next;
		free(temp);
	}
}

void	clean_everything()
{
	if (pthread_mutex_destroy(philo()->mutex_is_dead) != 0)
		printf("Error destroying mutex\n");
	free(philo()->mutex_is_dead);
	if (pthread_mutex_destroy(philo()->mutex_message) != 0)
		printf("Error destroying mutex\n");
	free(philo()->mutex_message);
	if (pthread_mutex_destroy(philo()->mutex_monitor) != 0)
		printf("Error destroying mutex\n");
	free(philo()->mutex_monitor);
	forks();
	philos();
}