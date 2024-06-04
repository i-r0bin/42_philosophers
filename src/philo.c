/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <rilliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:27 by rilliano          #+#    #+#             */
/*   Updated: 2024/04/04 14:02:21 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (check_input(argc, argv) != 0)
		return (1);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	philo = (t_philo *)malloc(sizeof(t_philo) * data.tot_philos);
	if (!philo)
		return (1);
	if (init_philo(&data, philo) != 0)
	{
		free(philo);
		return (1);
	}
	ft_create_threads(&data, philo);
	free_data(&data, philo);
	return (0);
}
