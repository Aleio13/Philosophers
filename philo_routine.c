/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:21:00 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/05 19:46:55 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->state);
	end = table->end_sim;
	pthread_mutex_unlock(&table->state);
	return (end);
}

int	go_eat(t_table *table, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
				usleep (500);
		pthread_mutex_lock(philo->l_fork);
		if (!print_status(philo, table, "is taking a fork") || \
		should_end(table))
			return (pthread_mutex_unlock(philo->l_fork), 0);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		if (!print_status(philo, table, "is taking a fork") || \
		should_end(table))
			return (pthread_mutex_unlock(philo->r_fork), 0);
		pthread_mutex_lock(philo->l_fork);
	}
	if (!print_status(philo, table, "is eating") || should_end(table))
		return (pthread_mutex_unlock(philo->l_fork),
		pthread_mutex_unlock(philo->r_fork), 0);
	philo->l_meal = get_time();
	philo->n_meals++;
	ft_sleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

int	go_think(t_table *table, t_philo *philo)
{
	if (!print_status(philo, table, "is thinking") || should_end(table))
		return (0);
	return (1);
}

int	go_sleep(t_table *table, t_philo *philo)
{
	if (!print_status(philo, table, "is sleeping") || should_end(table))
		return (0);
	ft_sleep(philo->rules->time_to_sleep);
	return (1);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->rules->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!should_end(table))
	{
		if (!go_eat(table, philo))
			break ;
		if (!go_sleep(table, philo))
			break ;
		if (!go_think(table, philo))
			break ;
	}
	return (NULL);
}

void	*start_monitor(void *arg)
{
	t_table	*table;
	t_rules	*rules;
	int		ate;
	int		i;

	table = (t_table *)arg;
	rules = table->philos->rules;
	while (!should_end(table))
	{
		ate = 1;
		i = -1;
		while (++i < rules->num_of_philos)
		{
			if (!check_philo(&table->philos[i], table))
				ate = 0;
			if (should_end(table))
				break ;
		}
		if (rules->must_eat > 0 && ate)
		{
			pthread_mutex_lock(&table->state);
			table->end_sim = 1;
			pthread_mutex_unlock(&table->state);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int			i;
	t_rules		*rules;
	pthread_t	monitor;

	rules = table->philos->rules;
	rules->table = table;
	i = -1;
	while (++i < rules->num_of_philos)
		table->philos[i].l_meal = get_time();
	i = -1;
	while (++i < rules->num_of_philos)
		pthread_create(&table->philos[i].tid, NULL, start_routine, &table->philos[i]);
	pthread_create(&monitor, NULL, start_monitor, table);
	i = -1;
	while (++i < rules->num_of_philos)
		pthread_join(table->philos[i].tid, NULL);
	pthread_join(monitor, NULL);
}
