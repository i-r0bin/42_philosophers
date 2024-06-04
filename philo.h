/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:35:22 by rilliano          #+#    #+#             */
/*   Updated: 2024/04/04 13:43:52 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				tot_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				tot_meals;
	int				end;
	unsigned long	start;
	struct s_philo	*first_philo;
	pthread_mutex_t	print;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
	int				eat_count;
	unsigned long	last_meal;
	pthread_t		thread;
}	t_philo;

int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_usleep(int time);
unsigned long	ft_get_time(void);
void			ft_print_status(t_philo *philo, char *status);
int				get_left_fork_pos(t_philo *philo);
int				take_left_fork(t_philo *philo);
int				take_right_fork(t_philo *philo);
int				take_forks(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			ft_think(t_philo *philo);
void			*philo_routine(void *arg);
void			ft_create_threads(t_data *data, t_philo *philo);
int				check_input(int argc, char **argv);
int				init_data(t_data *data, int argc, char **argv);
int				init_philo(t_data *data, t_philo *philo);
int				check_meals(t_data *data);
void			check_death(t_philo *philo);
void			free_data(t_data *data, t_philo *philo);
int				get_right_pos(t_philo *philo);

#endif
