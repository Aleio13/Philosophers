/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:21:00 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/04 23:06:15 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_eat(t_table *table, t_philo *philo)
{
	if (!print_status(philo, table, "has taken a fork"))
		return (0);
	pthread_mutex_lock(philo->l_fork);
	if (!print_status(philo, table, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	pthread_mutex_lock(philo->r_fork);
	if (!print_status(philo, table, "is eating"))
	{
		pthread_mutex_unlcok(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	philo->l_meal = get_time();
	philo->n_meals++;
	if (!ft_sleep(philo->rules->time_to_eat))
		error_msg("get_time failed", table);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	go_think(t_philo *philo, t_table *table)
{
	if (!print_status(philo, table, "is thinking"))
		return (0);
	return (1);
}

int	go_sleep(t_philo *philo, t_table *table)
{
	if (!print_status(philo, table, "is sleeping"))
		return (0);
	if (!ft_sleep(table->philos->rules->time_to_sleep))
		error_msg("get_time failed", table);
	return (1);
}

int	start_routine(t_table *table)
{
	t_philo	*philo;

	philo = table->philos;
	while (!table->end_sim)
	{
		if (!go_eat(table, philo))
			return (0);
		if (!go_sleep(table, philo))
			return (0);
		if (!go_think(table, philo))
			return (0);
	}
	return (1);
}

void	start_sim(t_table *table)
{
	int	i;
	int	is_full;
	t_rules	*rules;

	rules = table->philos->rules;
	while (!table->end_sim)
	{
		is_full = 0;
		
	}
}
