#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_program
{
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_philos;
	int				max_meals;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_program;

struct s_philo
{
	int				id;
	int				meals_eaten;
	int				eating;
	long			last_meal;
	t_program		*program;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
};

// Utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
long	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	print_message(char *str, t_philo *philo, int id);
size_t	ft_strlen(const char *str);


// Cleanup
void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks);
void	clean_exit(t_program *program, pthread_mutex_t *forks);

// Init
void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_input(t_philo *philo, char **argv);
void	setup_philosopher_data(t_philo *philos, t_program *program,
			char **argv, int count);
void	assign_forks_to_philos(t_philo *philos, pthread_mutex_t *forks,
			int total);

// Threads
int		thread_create(t_program *program, pthread_mutex_t *forks);
void	*philo_routine(void *pointer);
int		is_simulation_over(t_philo *philo);
void	eat_routine(t_philo *philo);

// Monitor
void	*monitor_routine(void *pointer);

#endif