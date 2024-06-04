/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:15 by rilliano          #+#    #+#             */
/*   Updated: 2024/04/04 18:34:52 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (take_left_fork(philo) != 0)
		return (1);
	if (take_right_fork(philo) != 0)
	{
		pthread_mutex_unlock(&philo->data->forks[get_left_fork_pos(philo)]);
		return (1);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	ft_print_status(philo, "is eating");
	philo->last_meal = ft_get_time();
	ft_usleep(philo->data->time_to_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->forks[get_left_fork_pos(philo)]);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	if (philo->data->time_to_die < ((int)(ft_get_time()
			- philo->last_meal) + philo->data->time_to_sleep))
	{
		ft_usleep(philo->data->time_to_die - (int)(ft_get_time()
				- philo->last_meal) + 5);
		check_death(philo);
	}
	else
		ft_usleep(philo->data->time_to_sleep);
}

int	get_right_pos(t_philo *philo)
{
	if (philo->id == philo->data->tot_philos)
		return (0);
	else
		return (philo->id);
}

void	ft_think(t_philo *philo)
{
	int		wait;
	int		time_left;
	t_philo	*first;

	if (philo->data->end == 0)
	{
		ft_print_status(philo, "is thinking");
		first = philo->data->first_philo;
		if ((int)(ft_get_time() - first[get_left_fork_pos(philo)].last_meal)
			> (int)(ft_get_time() - first[get_right_pos(philo)].last_meal))
			wait = (int)(ft_get_time()
					- first[get_left_fork_pos(philo)].last_meal);
		else
			wait = (int)(ft_get_time()
					- first[get_right_pos(philo)].last_meal);
		time_left = philo->data->time_to_die
			- (int)((ft_get_time() - philo->last_meal));
		if (wait > 0 && time_left < wait && wait < philo->data->time_to_eat)
		{
			ft_usleep(time_left + 1);
			check_death(philo);
		}
	}
}
