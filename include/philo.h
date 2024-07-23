#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

typedef enum e_errors
{
	INVALIDARGC,
	INVALIDARGV,
	INVALIDTS,
	ERRORDINNER,
	PTHREADCREATE,
}	t_errors;

typedef enum e_pstate{
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_FORK,
	DIED,
}	t_pstate;

typedef struct s_forks{
	pthread_mutex_t	mut;
	int 	fork_id;
}	t_forks;

typedef struct s_philo{
	int				philo_id;
	t_forks			*first_fork;
	t_forks			*second_fork;
	int				meals_nbr;
	bool			finished_eating;
	long			time_since_eat;
	pthread_t		thread_id;
	pthread_mutex_t mutex_philo;
}	t_philo;


typedef struct s_program{
	long			num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			eat_times;
	long			time_start;
	bool			finished;
	bool			ready_to_start;
	pthread_mutex_t	mutex_prog;
	pthread_mutex_t	mutex_write;
	pthread_t		monitor;
	t_forks			*forks;
	t_philo			*philos;
}	t_program;

int			check_args(int argc, char **argv);
void		error_message(int num);
int			check_if_num(char *str);
long		ft_atol(char *str);
int			init_dinner();
t_program	*philo();
void		dinner_init(void);
//void		wait_everyone();
long		get_time();
void		print_status(t_pstate status, t_philo *data);
void		join_threads();
void		*monitor_deaths();
void		join_monitor();
void		final_clean();

#endif