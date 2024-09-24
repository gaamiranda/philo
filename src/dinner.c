#include "../include/philo.h"

static void	monitor_dd(void)
{
	int		i;
	t_philo	*cur;

	cur = philo()->philos;
	i = 0;
	while (cur && i != philo()->num_philos)
	{
		pthread_mutex_lock(philo()->mutex_monitor);
		if (cur->meals_nbr == philo()->nbr_meals)
			i++;
		if (tv_since_start() >= cur->time_until_dead
			&& cur->meals_nbr != philo()->nbr_meals)
		{
			pthread_mutex_unlock(philo()->mutex_monitor);
			pthread_mutex_lock(philo()->mutex_is_dead);
			philo()->is_dead = 1;
			pthread_mutex_unlock(philo()->mutex_is_dead);
			print_status(cur, DIED);
			return ;
		}
		pthread_mutex_unlock(philo()->mutex_monitor);
		if (philo()->num_philos != 1)
			cur = cur->next;
	}
	return ;
}

static void	sleep_tight(t_philo *data)
{
	if (!someone_dead())
		return ;
	print_status(data, SLEEPING);
	only_sleep(philo()->time_sleep);
}

static void	eat(t_philo *data)
{
	pthread_mutex_t	*one;
	pthread_mutex_t	*two;

	if (!someone_dead())
		return ;
	one = data->first_fork->mut;
	two = data->second_fork->mut;
	if (data->philo_id % 2 == 0)
	{
		one = data->second_fork->mut;
		two = data->first_fork->mut;
	}
	pthread_mutex_lock(one);
	pthread_mutex_lock(two);
	pthread_mutex_lock(philo()->mutex_monitor);
	data->time_until_dead = tv_since_start() + philo()->time_die;
	data->meals_nbr++;
	pthread_mutex_unlock(philo()->mutex_monitor);
	print_status(data, TAKEN_FORK);
	print_status(data, TAKEN_FORK);
	print_status(data, EATING);
	only_sleep(philo()->time_eat);
	pthread_mutex_unlock(two);
	pthread_mutex_unlock(one);
	sleep_tight(data);
}

static void	*routine(void *dat)
{
	t_philo	*data;

	data = (t_philo *)dat;
	if (data->philo_id % 2 != 0)
		only_sleep((philo()->time_eat * 2) - philo()->time_sleep);
	while (someone_dead() && data->meals_nbr != philo()->nbr_meals)
	{
		eat(data);
		if (philo()->num_philos % 2 == 0
			&& philo()->time_eat == philo()->time_sleep)
			continue ;
		if (someone_dead() && data->meals_nbr != philo()->nbr_meals)
		{
			print_status(data, THINKING);
			only_sleep((philo()->time_eat * 2) - philo()->time_sleep);
		}
	}
	if (someone_dead() && data->meals_nbr != philo()->nbr_meals)
		print_status(data, THINKING);
	return (NULL);
}

void	dinner_init(void)
{
	int		i;
	t_philo	*cur;

	i = -1;
	cur = philo()->philos;
	if (pthread_create(&philo()->monitor, NULL, (void *)monitor_dd, NULL) != 0)
		return ;
	if (philo()->num_philos == 1)
		return (handle_one_philo());
	while (++i < philo()->num_philos)
	{
		if (pthread_create(&cur->thread_id, NULL, routine, cur) != 0)
			return ;
		cur = cur->next;
	}
	cur = philo()->philos;
	i = 0;
	if (pthread_join(philo()->monitor, NULL) != 0)
		return ;
	while (++i <= philo()->num_philos)
	{
		if (pthread_join(cur->thread_id, NULL) != 0)
			return ;
		cur = cur->next;
	}
}
