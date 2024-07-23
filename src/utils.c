#include "../include/philo.h"

long	tv_since_start()
{
	struct timeval	tv;
	long			temp;

	gettimeofday(&tv, NULL);
	temp = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philo()->start_time;
	return temp;
}

void	print_status(t_philo *data, t_pstate code)
{
	pthread_mutex_lock(philo()->mutex_message);
	if (code == TAKEN_FORK)
		printf("%ld %d has taken a fork\n", tv_since_start(), data->philo_id);
	else if (code == EATING)
		printf("%ld %d is eating\n", tv_since_start(), data->philo_id);
	else if (code == THINKING)
		printf("%ld %d is thinking\n", tv_since_start(), data->philo_id);
	else if (code == SLEEPING)
		printf("%ld %d is sleeping\n", tv_since_start(), data->philo_id);
	else if (code == DIED)
		printf("%ld %d died\n", tv_since_start(), data->philo_id);
	pthread_mutex_unlock(philo()->mutex_message);
}

void	only_sleep(long time)
{
	time += tv_since_start();
	while (tv_since_start() < time)
	{
		if (!someone_dead())
			return ;
		usleep(1e2);
	}
}

int		someone_dead()
{
	pthread_mutex_lock(philo()->mutex_is_dead);
	if (philo()->is_dead)
	{
		pthread_mutex_unlock(philo()->mutex_is_dead);
		return 0;
	}
	pthread_mutex_unlock(philo()->mutex_is_dead);
	return 1;
}