/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:41 by rilliano          #+#    #+#             */
/*   Updated: 2024/04/04 14:50:15 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->end == 0)
	{
		printf("%ld %d %s\n", ft_get_time() - philo->data->start,
			philo->id, status);
		if (ft_strncmp(status, "died", 4) == 0)
		{
			pthread_mutex_lock(&philo->data->end_mutex);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->end_mutex);
		}
	}
	pthread_mutex_unlock(&philo->data->print);
}

int	get_left_fork_pos(t_philo *philo)
{
	if (philo->id == 1)
		return (philo->data->tot_philos - 1);
	else
		return (philo->id - 2);
}

int	take_left_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[get_left_fork_pos(philo)]) != 0)
		return (1);
	ft_print_status(philo, "has taken a fork");
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	if (philo->data->tot_philos == 1
		|| pthread_mutex_lock(&philo->data->forks[philo->id - 1]) != 0)
		return (1);
	ft_print_status(philo, "has taken a fork");
	return (0);
}
