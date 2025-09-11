/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:21:00 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/11 02:57:16 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(pthread_mutex_t *fork, t_philo *philo, t_table *table, char *msg)
{
	pthread_mutex_lock(fork);
	if (should_end(table))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	if (!print_status(philo, table, msg))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	return (1);
}

int	eating_process(t_philo *philo, t_table *table)
{
	if (should_end(table))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	if (!print_status(philo, table, "is eating"))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	ft_sleep(philo->rules->time_to_eat);
	pthread_mutex_lock(&table->state);
	philo->l_meal = get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&table->state);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

int	go_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->rules->num_of_philos == 1)
		return (one_philo(table));
	if (philo->id % 2 == 1)
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	else
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	if (!take_fork(first, philo, table, "has taken a fork"))
		return (0);
	if (!take_fork(second, philo, table, "has taken a fork"))
		return (pthread_mutex_unlock(first), 0);
	return (eating_process(philo, table));
}

int	go_think(t_table *table, t_philo *philo)
{
	if (!print_status(philo, table, "is thinking"))
		return (0);
	return (1);
}

int	go_sleep(t_table *table, t_philo *philo)
{
	if (!print_status(philo, table, "is sleeping"))
		return (0);
	ft_sleep(philo->rules->time_to_sleep);
	return (1);
}
