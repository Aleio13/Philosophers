/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:28:36 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/03 18:59:57 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_check_rules(t_rules *rules)
{
	printf("Number of Philo: %d\n", rules->num_of_philos);
	printf("Time of death: %d\n", rules->time_to_die);
	printf("Time to eat: %d\n", rules->time_to_eat);
	printf("time to sleep: %d\n", rules->time_to_sleep);
	printf("Number of time to eat: %d\n", rules->must_eat);
}

void	print_check_philos(t_philo *philos, t_rules *rules)
{
	int	n_philos;
	int	i;

	i = 0;
	n_philos = rules->num_of_philos;
	while (i < n_philos)
	{
		printf("ID: %d\n", philos->id);
		printf("Hungry: %d\n", philos->hungry);
		printf("Last meal: %ld\n", philos->l_meal);
		printf("left fork: %p\n", philos->l_fork);
		printf("Right fork: %p\n", philos->r_fork);
		i++;
	}
}

void	print_check_table(t_table *table)
{
	printf("Num of philos: %d\n", table->philos->rules->num_of_philos);
	printf("Num of forks: %d\n", table->philos->rules->num_of_philos);
	printf("Start Simulation: %ld\n", table->start_sim);
	printf("End sim: %d\n", table->end_sim);
	printf("State adress: %d\n", table->state);
	printf("Print address: %d\n", table->print);
}

void	cleanup_table(t_table *table)
{
	int				i;
	int				n_philos;

	i = 0;
	n_philos = table->philos->rules->num_of_philos;
	if (!table)
		return ;
	if (table->forks)
	{
		while (i < n_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	if (table->philos)
		free(table->philos);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->state);
}

int main(int arc, char **arv)
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
		return (1);
	table = init_table(rules);
	print_check(rules);
	free(rules);
	return (0);
}
