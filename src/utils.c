#include "../include/philo.h"

long	tv_since_start(void)
{
	struct timeval	tv;
	long			temp;

	gettimeofday(&tv, NULL);
	temp = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philo()->start_time;
	return (temp);
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

int	someone_dead(void)
{
	pthread_mutex_lock(philo()->mutex_is_dead);
	if (philo()->is_dead)
	{
		pthread_mutex_unlock(philo()->mutex_is_dead);
		return (0);
	}
	pthread_mutex_unlock(philo()->mutex_is_dead);
	return (1);
}

void	h1(void)
{
	t_philo	*cur;

	cur = philo()->philos;
	print_status(cur, TAKEN_FORK);
	while (1)
	{
		pthread_mutex_lock(philo()->mutex_is_dead);
		if (philo()->is_dead == 1)
		{
			pthread_mutex_unlock(philo()->mutex_is_dead);
			break ;
		}
		pthread_mutex_unlock(philo()->mutex_is_dead);
		usleep(200);
	}
}

void	handle_one_philo(void)
{
	t_philo	*cur;

	cur = philo()->philos;
	pthread_create(&cur->thread_id, NULL, (void *)h1, NULL);
	if (pthread_join(philo()->monitor, NULL) != 0)
		return ;
	if (pthread_join(philo()->philos->thread_id, NULL) != 0)
		return ;
}
