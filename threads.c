#include "philo.h"
// Thread-safe read of dead_flag

int	is_simulation_over(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->program->dead_lock);
	result = philo->program->dead_flag;
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (result);
}

// Handle single philosopher case
static int	handle_single_philo(t_philo *philo)
{
	if (philo->program->num_philos == 1)
	{
		ft_usleep(philo->program->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

// Pick up forks
static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if (handle_single_philo(philo))
		return ;
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
}

// Update meal information
static void update_meal_info(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->meal_lock);
    print_message("is eating", philo, philo->id);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->program->meal_lock);
}

// Release forks
static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void finish_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->meal_lock);
    philo->eating = 0;
    pthread_mutex_unlock(&philo->program->meal_lock);
}

// Routine for eating
void	eat_routine(t_philo *philo)
{
	take_forks(philo);
	if (philo->program->num_philos == 1)
		return ;
	update_meal_info(philo);
	ft_usleep(philo->program->time_to_eat);
    finish_eating(philo);  
	drop_forks(philo);
}

// Sleeping routine
static void	sleep_routine(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->program->time_to_sleep);
}

// Thinking routine
static void	think_routine(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_simulation_over(philo))
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (pointer);
}

// Create all philosopher threads
static int	create_philo_threads(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->philos[0].program->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				&philo_routine, &program->philos[i]) != 0)
			destroy_all("Thread creation error\n", program, forks);
		i++;
	}
	return (0);
}

// Join all philosopher threads
static int	join_philo_threads(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->philos[0].program->num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error\n", program, forks);
		i++;
	}
	return (0);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;

	if (pthread_create(&observer, NULL, &monitor_routine,
			program->philos) != 0)
		destroy_all("Thread creation error\n", program, forks);
	create_philo_threads(program, forks);
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error\n", program, forks);
	join_philo_threads(program, forks);
	return (0);
}
