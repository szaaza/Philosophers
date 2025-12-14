#include "philo.h"

void	setup_philosopher_data(t_philo *philos, t_program *program,
		char **argv, int count)
{
	int	idx;

	idx = 0;
	while (idx < count)
	{
		philos[idx].id = idx + 1;
		philos[idx].meals_eaten = 0;
		philos[idx].eating = 0;
		philos[idx].program = program;
		init_input(&philos[idx], argv);
		philos[idx].last_meal = get_current_time();
		idx++;
	}
}

void	assign_forks_to_philos(t_philo *philos, pthread_mutex_t *forks,
		int total)
{
	int	j;

	j = 0;
	while (j < total)
	{
		philos[j].l_fork = &forks[j];
		if (j == 0)
			philos[j].r_fork = &forks[total - 1];
		else
			philos[j].r_fork = &forks[j - 1];
		j++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	program->start_time = get_current_time();
}