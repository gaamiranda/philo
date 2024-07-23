#include "../include/philo.h"

t_program	*philo()
{
	static t_program	philo;

	return (&philo);
}

int		init_struct(char **argv, int argc)
{
	philo()->num_philo = ft_atol(argv[1]);
	philo()->time_die = ft_atol(argv[2]) * 1000;
	philo()->time_eat = ft_atol(argv[3]) * 1000;
	philo()->time_sleep = ft_atol(argv[4]) * 1000;
	if (philo()->time_eat < 60000 
		|| philo()->time_die < 60000 
		|| philo()->time_sleep < 60000)
		return 1;
	if (argc == 6)
		philo()->eat_times = ft_atol(argv[5]);
	else
		philo()->eat_times = -1;
	return 0;
}

int main(int argc, char **argv)
{
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
	if (init_struct(argv, argc) != 0)
	{
		error_message(INVALIDTS);
		return 3;
	}
	if (init_dinner() != 0)
	{
		error_message(ERRORDINNER);
		return 4;
	}
	dinner_init();
	final_clean();
	return 0;
}

/**
 * para dar free a:
 * philo()->forks
 * philo()->philos
 * nao esquecer mutex_destroy em todos os forks
 * 
 */