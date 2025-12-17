
#include "philo.h"

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid number of times to eat\n", 32), 1);
	return (0);
}
static void	initialize_simulation(t_program *program, t_philo *philos,
				pthread_mutex_t *forks, char **argv)
{
	init_program(program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	setup_philosopher_data(philos, program, argv, ft_atoi(argv[1]));
	assign_forks_to_philos(philos, forks, ft_atoi(argv[1]));
}
static void	run_simulation(t_program *program, pthread_mutex_t *forks)
{
	thread_create(program, forks);
}

#include <stdio.h> // Required for ucheck printf

void	ucheck(t_program *program, t_philo *philos, int count)
{
	int	i;
	
	printf("\n=== UCHECK DIAGNOSTICS ===\n");
	printf("Start Time: %ld\n", program->start_time);
	printf("Philosophers: %d\n", count);
	printf("------------------------------------------\n");
	
	i = 0;
	while (i < count)
	{
		printf("[Philo %d]\n", philos[i].id);
		// Check 1: Verify Fork Pointers exist
		if (!philos[i].l_fork || !philos[i].r_fork)
		printf("  ERROR: Fork pointers are NULL!\n");
		else
		{
			// Check 2: Print addresses to visualize the circle
			printf("  Left Fork Addr:  %p\n", (void *)philos[i].l_fork);
			printf("  Right Fork Addr: %p\n", (void *)philos[i].r_fork);
			
			// Check 3: Logic Verification (Circular Table)
			// The Left fork of current philo should be the Right fork of the next philo
			// (depending on your specific index logic in init.philo.c)
			if (i < count - 1)
			{
				if (philos[i].l_fork == philos[i + 1].r_fork)
				printf("  OK: Shared fork verified with Philo %d\n", philos[i+1].id);
				else
				printf("  WARNING: Fork logic might be broken between %d and %d\n", 
					philos[i].id, philos[i+1].id);
				}
			}
			i++;
		}
		printf("=== UCHECK COMPLETE ===\n\n");
	}
	


int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_valid_args(argv) == 1)
		return (1);
	initialize_simulation(&program, philos, forks, argv);

	run_simulation(&program, forks);

	return (0);
}