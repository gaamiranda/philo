#include "../include/philo.h"

t_program	*philo()
{
	static t_program	philo;

	return (&philo);
}

static pthread_mutex_t	*mutex_create()
{
	pthread_mutex_t *mut;

	mut = malloc(sizeof(pthread_mutex_t));
	if (!mut)
		return (NULL);
	if (pthread_mutex_init(mut, NULL) != 0)
	{
		printf("Error initializing mutex\n");
		return NULL;
	}
	return mut;
}

int		init_struct(char **argv, int argc)
{
	struct timeval	tv;

	philo()->num_philos = ft_atol(argv[1]);
	philo()->time_die = ft_atol(argv[2]);
	philo()->time_eat = ft_atol(argv[3]);
	philo()->time_sleep = ft_atol(argv[4]);
	if (philo()->time_eat < 60 
		|| philo()->time_die < 60 
		|| philo()->time_sleep < 60 || philo()->num_philos == 0)
		return 1;
	if (argc == 6)
		philo()->nbr_meals = ft_atol(argv[5]);
	else
		philo()->nbr_meals = -1;
	if (philo()->num_philos > 200)
		return (2);
	philo()->is_dead = 0;
	philo()->monitor = 0;
	philo()->mutex_is_dead = mutex_create();
	philo()->mutex_message = mutex_create();
	philo()->mutex_monitor = mutex_create();
	gettimeofday(&tv, NULL);
	philo()->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	init_philos();
	return 0;
}

int main(int argc, char **argv)
{
	int status_code;

	status_code = 0;
	if (check_args(argc, argv) == 1)
	{
		error_message(INVALIDARGC);
		return 1;
	}
	else if (check_args(argc, argv) == 2)
	{
		error_message(INVALIDARGV);
		return 2;
	}
	status_code = init_struct(argv, argc);
	if (status_code != 0)
	{
		if (status_code == 2)
			error_message(INVALIDNP);
		else
			error_message(INVALIDTS);
		return 3;
	}
	dinner_init();
	clean_everything();
	return 0;
}
