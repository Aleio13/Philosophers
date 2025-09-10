/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:28:36 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/11 00:28:34 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_table(t_table *table, t_rules *rules)
{
	int	i;
	int	n_philos;

	i = 0;
	if (table)
	{
		n_philos = table->philos->rules->num_of_philos;
		if (table->forks)
		{
			while (i < n_philos)
			{
				pthread_mutex_destroy(&table->forks[i]);
				i++;
			}
			free(table->forks);
		}
		pthread_mutex_destroy(&table->print);
		pthread_mutex_destroy(&table->state);
		if (table->philos)
			free(table->philos);
		if (table)
			free(table);
	}
	if (rules)
		free(rules);
}

int	check_rules(t_rules *rules)
{
	if (rules->num_of_philos > 200)
		return (0);
	if (rules->time_to_die < 60)
		return (0);
	if (rules->time_to_eat < 60)
		return (0);
	if (rules->time_to_sleep < 60)
		return (0);
	return (1);
}

int	main(int arc, char **arv)
{
	t_rules	*rules;
	t_table	*table;

	if (arc < 5 || arc > 6)
	{
		wrong_args();
		return (1);
	}
	rules = init_rules(arc, arv);
	if (!rules)
		return (0);
	// if (!check_rules(rules))
	// {
	// 	wrong_args();
	// 	free(rules);
	// 	return (0);
	// }
	table = init_table(rules);
	if (table)
		start_simulation(table);
	cleanup_table(table, rules);
	return (0);
}
