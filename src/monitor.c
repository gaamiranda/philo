#include "../include/philo.h"

bool	philo_dead(t_philo *philo_data)
{
	long	elapsed;

	pthread_mutex_lock(&philo_data->mutex_philo);
	if (philo_data->finished_eating)
	{
		pthread_mutex_unlock(&philo_data->mutex_philo);
		return false;
	}
	pthread_mutex_unlock(&philo_data->mutex_philo);
	pthread_mutex_lock(&philo_data->mutex_philo);
	elapsed = get_time() - philo_data->time_since_eat;
	pthread_mutex_unlock(&philo_data->mutex_philo);
	if (elapsed > (philo()->time_die / 1000))
		return true;
	return false;
}

void	*monitor_deaths()
{
	int		i;

	while (!philo()->finished)
	{
		i = -1;
		while (++i < philo()->num_philo && !philo()->finished)
		{
			if (philo_dead(&philo()->philos[i]))
			{
				pthread_mutex_lock(&(philo()->mutex_prog));
				philo()->finished = true;
				pthread_mutex_unlock(&(philo()->mutex_prog));
				print_status(DIED, &philo()->philos[i]);
			}
		}
	}
	return NULL;
}
