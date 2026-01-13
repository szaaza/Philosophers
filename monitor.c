#include "philo.h"

// Get time since last meal safely
long	get_time_since_last_meal(t_philo *philo)
{
	long	time_elapsed;
	long	current_time;

	pthread_mutex_lock(&philo->program->meal_lock);
	current_time = get_current_time();
	time_elapsed = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->program->meal_lock);
	return (time_elapsed);
}

// Check if philosopher is currently eating
int	is_currently_eating(t_philo *philo)
{
	int	eating_status;

	pthread_mutex_lock(&philo->program->meal_lock);
	eating_status = philo->eating;
	pthread_mutex_unlock(&philo->program->meal_lock);
	return (eating_status);
}

// Announce death and set dead flag
static void	announce_death(t_philo *philo)
{
	print_message("died", philo, philo->id);
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->program->dead_flag = 1;
	pthread_mutex_unlock(&philo->program->dead_lock);
}

// Check if a single philosopher has died
static int	has_philosopher_died(t_philo *philo)
{
	long	time_elapsed;
	long	current_time;
	int		eating_status;

	pthread_mutex_lock(&philo->program->meal_lock);
	current_time = get_current_time();
	time_elapsed = current_time - philo->last_meal;
	eating_status = philo->eating;
	pthread_mutex_unlock(&philo->program->meal_lock);
	
	if (time_elapsed >= philo->program->time_to_die && !eating_status)
	{
		announce_death(philo);
		return (1);
	}
	return (0);
}

// Check all philosophers for death
static int	check_for_death(t_philo *philos, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (has_philosopher_died(&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

// Get number of meals eaten by a philosopher
static int	get_meals_eaten(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->program->meal_lock);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->program->meal_lock);
	return (meals);
}

// Check if a philosopher has finished eating required meals
static int	has_finished_eating(t_philo *philo, int max_meals)
{
	if (max_meals == -1)
		return (0);
	if (get_meals_eaten(philo) >= max_meals)
		return (1);
	return (0);
}

// Count how many philosophers finished eating
static int	count_finished_philos(t_philo *philos, int num_philos)
{
	int	i;
	int	finished_count;
	int	max_meals;

	i = 0;
	finished_count = 0;
	max_meals = philos[0].program->max_meals;
	if (max_meals == -1)
		return (0);
	while (i < num_philos)
	{
		if (has_finished_eating(&philos[i], max_meals))
			finished_count++;
		i++;
	}
	return (finished_count);
}

// Stop simulation by setting dead flag
static void	stop_simulation(t_program *program)
{
	pthread_mutex_lock(&program->dead_lock);
	program->dead_flag = 1;
	pthread_mutex_unlock(&program->dead_lock);
}

// Check if all philosophers ate enough meals
static int	all_philos_ate_enough(t_philo *philos, int num_philos)
{
	int	finished_count;

	finished_count = count_finished_philos(philos, num_philos);
	if (finished_count == num_philos)
	{
		stop_simulation(philos[0].program);
		return (1);
	}
	return (0);
}

// Main monitoring loop
void	*monitor_routine(void *pointer)
{
	t_philo	*philos;
	int		num_philos;

	philos = (t_philo *)pointer;
	num_philos = philos[0].program->num_philos;
	while (1)
	{
		if (check_for_death(philos, num_philos))
			break ;
		if (all_philos_ate_enough(philos, num_philos))
			break ;
		usleep(1000);
	}
	return (NULL);
}
