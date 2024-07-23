#include "../include/philo.h"

void	assign_forks(int pos, t_forks *forks, t_philo *philos)
{
	int		nr;

	nr = philo()->num_philo;
	if (philos[pos].philo_id % 2 == 0)
	{
		//printf("id: %d entrou no par\n", pos);
		philos[pos].first_fork = &forks[pos];
		philos[pos].second_fork = &forks[(pos + 1) % nr];
	}
	else
	{
		//printf("id: %d entrou no impar\n", pos);
		philos[pos].first_fork = &forks[(pos + 1) % nr];
		philos[pos].second_fork = &forks[pos];
	}
}

void	philo_init()
{
	int		i;

	i = 0;
	while (i < philo()->num_philo)
	{
		philo()->philos[i].philo_id = i + 1;
		philo()->philos[i].finished_eating = false;
		philo()->philos[i].meals_nbr = 0;
		pthread_mutex_init(&(philo())->philos[i].mutex_philo, NULL);
		assign_forks(i, philo()->forks, philo()->philos);
		i++;
	}
}

int		init_dinner()
{
	int		i;

	i = 0;
	philo()->forks = malloc(sizeof(t_forks) * philo()->num_philo);
	if (!philo()->forks)
		return 1;
	if (pthread_mutex_init(&(philo())->mutex_prog, NULL) != 0)
			return 2;
	if (pthread_mutex_init(&(philo())->mutex_write, NULL) != 0)
			return 2;
	philo()->philos = malloc(sizeof(t_philo) * philo()->num_philo);
	if (!philo()->philos)
		return 1;
	philo()->finished = false;
	while (i < philo()->num_philo)
	{
		if (pthread_mutex_init(&(philo())->forks[i].mut, NULL) != 0)
			return 2;
		philo()->forks[i].fork_id = i;
		i++;
	}
	philo_init();
	return 0;
}
