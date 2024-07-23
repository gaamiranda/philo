#include "../include/philo.h"

long	get_time()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		printf("time of days failed\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}



void	join_threads()
{
	int		i;

	i = 0;
	while (i < philo()->num_philo)
	{
		if (pthread_join(philo()->philos[i].thread_id, NULL) != 0)
			printf("Failed to join");
		i++;
	}
}

void	print_status(t_pstate status, t_philo *data)
{
	long	elapsed;

	elapsed = get_time() - philo()->time_start;
	if (data->finished_eating)
		return ;
	pthread_mutex_lock(&(philo())->mutex_write);
	if ((status == TAKEN_FORK) && !philo()->finished)
		printf("%ld %d has taken a fork\n", elapsed, data->philo_id);
	else if (status == EATING && !philo()->finished)
		printf("%ld %d is eating\n", elapsed, data->philo_id);
	else if (status == SLEEPING && !philo()->finished)
		printf("%ld %d is sleeping\n", elapsed, data->philo_id);
	else if (status == THINKING && !philo()->finished)
		printf("%ld %d is thinking\n", elapsed, data->philo_id);
	else if (status == DIED)
		printf("%ld %d died\n", elapsed, data->philo_id);
	pthread_mutex_unlock(&(philo())->mutex_write);
}

void	join_monitor()
{
	pthread_mutex_lock(&philo()->mutex_prog);
	philo()->finished = true;
	pthread_mutex_unlock(&philo()->mutex_prog);
	pthread_join(philo()->monitor, NULL);
}

void	final_clean()
{
	int		i;
	t_philo	*data;

	i = 0;
	while (i < philo()->num_philo)
	{
		data = &philo()->philos[i];
		pthread_mutex_destroy(&data->mutex_philo);
		i++;
	}
	pthread_mutex_destroy(&philo()->mutex_prog);
	pthread_mutex_destroy(&philo()->mutex_write);
	free(philo()->forks);
	free(philo()->philos);
}