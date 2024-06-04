/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:35:56 by rilliano          #+#    #+#             */
/*   Updated: 2024/04/04 14:43:42 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) <= 0 || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (1);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->tot_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->end = 0;
	if (argc == 6)
		data->tot_meals = ft_atoi(argv[5]);
	else
		data->tot_meals = -1;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
	data->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * data->tot_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->tot_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->start = 0;
	return (0);
}

int	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	data->first_philo = philo;
	i = 0;
	while (i < data->tot_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].eat_count = 0;
		philo[i].last_meal = 0;
		i++;
	}
	return (0);
}
