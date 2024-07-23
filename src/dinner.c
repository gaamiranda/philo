#include "../include/philo.h"

void	*one_philo()
{
	t_philo	*data;
	
	data = (t_philo *)&philo()->philos[0];
	while (!philo()->ready_to_start)
		;
	print_status(TAKEN_FORK, data);
	while(!philo()->finished)
		usleep(200);
	return NULL;
}

void	thinking(t_philo *data_philo)
{
	print_status(THINKING, data_philo);
}

void	eat(t_philo *data_philo)
{
	pthread_mutex_lock(&data_philo->first_fork->mut);
	print_status(TAKEN_FORK, data_philo);
	pthread_mutex_lock(&data_philo->second_fork->mut);
	print_status(TAKEN_FORK, data_philo);
	data_philo->time_since_eat = get_time();
	data_philo->meals_nbr++;
	print_status(EATING, data_philo);
	usleep(philo()->time_eat);
	if (philo()->eat_times && data_philo->meals_nbr == philo()->eat_times)
	{
		pthread_mutex_lock(&data_philo->mutex_philo);
		data_philo->finished_eating = true;
		pthread_mutex_unlock(&data_philo->mutex_philo);
	}
	pthread_mutex_unlock(&data_philo->first_fork->mut);
	pthread_mutex_unlock(&data_philo->second_fork->mut);
}
// long	get_time2()
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL))
// 		printf("time of days failed\n");
// 	return ((tv.tv_sec * 1e6) + tv.tv_usec);
// }

// void	better_usleep(long usec)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = get_time2();
// 	while (get_time2() - start < usec)
// 	{
// 		if (philo()->finished)
// 			break ;
// 		elapsed = get_time2() - start;
// 		rem = usec - elapsed;
// 		if (rem > 1e3)
// 			usleep(rem / 2);
// 		else
// 			while(get_time2() - start < usec)
// 				;
// 	}
// }

void	*dinner_create(void	*data)
{
	t_philo *data_philo;

	data_philo = (t_philo *)data;
	while (!philo()->ready_to_start)
		;
	pthread_mutex_lock(&data_philo->mutex_philo);
	data_philo->time_since_eat = get_time();
	pthread_mutex_unlock(&data_philo->mutex_philo);
	while (!philo()->finished)
	{
		if (data_philo->finished_eating)
			break ;
		eat(data_philo);
		print_status(SLEEPING, data_philo);
		//better_usleep(philo()->time_sleep);
		usleep(philo()->time_sleep);
		thinking(data_philo);
	}
	return NULL;
}

void	dinner_init(void)
{
	int		i;

	i = 0;
	if (philo()->eat_times == 0)
		return;
	if(philo()->num_philo == 1)
		pthread_create(&(philo())->philos[0].thread_id, NULL, one_philo, NULL);
	else
	{
		while (i < philo()->num_philo)
		{
			if (pthread_create(&(philo()->philos[i].thread_id), NULL, 
				dinner_create, &(philo()->philos[i])) != 0)
				error_message(PTHREADCREATE);
			i++;
		}
	}
	pthread_create(&(philo()->monitor), NULL, monitor_deaths, NULL);
	philo()->time_start = get_time();
	pthread_mutex_lock(&(philo())->mutex_prog);
	philo()->ready_to_start = true;
	pthread_mutex_unlock(&(philo())->mutex_prog);
	join_threads();
	//se chegar aqui significa que estao todos cheios
	join_monitor();
}
