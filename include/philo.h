#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdint.h>

typedef enum e_errors
{
	INVALIDARGC,
	INVALIDARGV,
	INVALIDTS,
	ERRORDINNER,
	PTHREADCREATE,
	INVALIDNP,
}	t_errors;

typedef enum e_mtx_codes
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
}	t_mtx_codes;

typedef enum e_thread_codes
{
	CREATE,
	JOIN,
}	t_thread_codes;

typedef enum e_pstate
{
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_FORK,
	DIED,
}	t_pstate;

typedef struct s_forks
{
	pthread_mutex_t	*mut;
	int				is_locked;
}	t_forks;

typedef struct s_philo
{
	int				philo_id;
	int				meals_nbr;
	long			time_until_dead;
	pthread_t		thread_id;
	t_forks			*first_fork;
	t_forks			*second_fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

typedef struct s_program
{
	long			is_dead;
	long			num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			nbr_meals;
	long			start_time;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*mutex_message;
	pthread_mutex_t	*mutex_is_dead;
	pthread_mutex_t	*mutex_monitor;
}	t_program;

int			check_args(int argc, char **argv);
void		error_message(int num);
int			check_if_num(char *str);
long		ft_atol(char *str);
t_program	*philo(void);
void		init_philos(void);
long		tv_since_start(void);
void		dinner_init(void);
void		forks_init(void);
void		print_status(t_philo *data, t_pstate code);
void		only_sleep(long time);
int			someone_dead(void);
void		clean_everything(void);
void		handle_one_philo(void);

#endif