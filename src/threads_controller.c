/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:54 by rilliano          #+#    #+#             */
/*   Updated: 2024/04/04 17:50:52 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tot_philos)
	{
		if (data->first_philo[i].eat_count < data->tot_meals)
			return (0);
		i++;
	}
	pthread_mutex_lock(&data->end_mutex);
	data->end = 1;
	pthread_mutex_unlock(&data->end_mutex);
	return (1);
}

void	check_death(t_philo *philo)
{
	if ((int)(ft_get_time() - philo->last_meal) > philo->data->time_to_die)
		ft_print_status(philo, "died");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat - 10);
	while (philo->data->end == 0)
	{
		if (take_forks(philo) == 0)
			ft_eat(philo);
		if (philo->data->tot_meals > 0 && check_meals(philo->data) == 1)
			break ;
		ft_sleep(philo);
		ft_think(philo);
		check_death(philo);
	}
	return (NULL);
}

void	ft_create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start = ft_get_time();
	while (i < data->tot_philos)
	{
		philo[i].last_meal = data->start;
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data->tot_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
