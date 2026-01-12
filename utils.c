#include "philo.h"

// Check if character is a digit
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
		return (0);
}

// Convert string to integer
int	ft_atoi(const char *s)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	nbr = 0;
	sign = 1;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		nbr = nbr * 10 + s[i] - 48;
		i++;
	}
	return (nbr * sign);
}

// Get current time in milliseconds
long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (write(2, "gettimeofday error\n", 20), -1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// Precise sleep function in milliseconds
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

// Thread-safe message printing
void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->program->write_lock);
	time = get_current_time() - philo->program->start_time;
	if (!is_simulation_over(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->program->write_lock);
}

// Initialize philosopher input data from command line arguments
void	init_input(t_philo *philo, char **argv)
{
	philo->program->num_philos = ft_atoi(argv[1]);
	philo->program->time_to_die = ft_atoi(argv[2]);
	philo->program->time_to_eat = ft_atoi(argv[3]);
	philo->program->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->program->max_meals = ft_atoi(argv[5]);
	else
		philo->program->max_meals = -1;
}

// Helper function for strlen
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

