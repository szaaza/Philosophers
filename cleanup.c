#include "philo.h"

// Print error message to stderr
static void	print_error(char *error_msg)
{
	if (error_msg)
		write(2, error_msg, ft_strlen(error_msg));
}

// Destroy all fork mutexes
static void	destroy_forks(pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

// Destroy program control mutexes
static void	destroy_program_mutexes(t_program *program)
{
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
}

// Cleanup and exit on error
void	destroy_all(char *error_msg, t_program *program, pthread_mutex_t *forks)
{
	print_error(error_msg);
	destroy_program_mutexes(program);
	destroy_forks(forks, program->num_philos);
	exit(1);
}

// Clean exit after successful simulation
void	clean_exit(t_program *program, pthread_mutex_t *forks)
{
	destroy_program_mutexes(program);
	destroy_forks(forks, program->num_philos);
}
