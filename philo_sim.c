/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:34:54 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/11 02:49:37 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->rules->table;
	if (philo->id % 2 == 0)
		ft_sleep(philo->rules->time_to_eat);
	while (1)
	{
		if (should_end(table) || !go_eat(table, philo))
			break ;
		if (should_end(table) || !go_think(table, philo))
			break ;
		if (should_end(table) || !go_sleep(table, philo))
			break ;
	}
	return (NULL);
}

void	*start_monitor(void *arg)
{
	t_table	*table;
	t_rules	*rules;
	int		status;

	table = (t_table *)arg;
	rules = table->philos->rules;
	while (!should_end(table))
	{
		status = check_all_philos(table, rules);
		if (status != 0)
			break ;
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
	table->start_sim = get_time();
	while (++i < rules->num_of_philos)
		table->philos[i].l_meal = get_time();
	i = -1;
	while (++i < rules->num_of_philos)
		pthread_create(&table->philos[i].tid, NULL, start_routine,
			&table->philos[i]);
	pthread_create(&monitor, NULL, start_monitor, table);
	i = -1;
	while (++i < rules->num_of_philos)
		pthread_join(table->philos[i].tid, NULL);
	pthread_join(monitor, NULL);
}
