/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:28:36 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/03 22:57:42 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_check_rules(t_rules *rules)
{
	printf("--------------RULE CHECKER:-----------------------------------------\n");
	printf("Number of Philo: %d\n", rules->num_of_philos);
	printf("Time of death: %d\n", rules->time_to_die);
	printf("Time to eat: %d\n", rules->time_to_eat);
	printf("time to sleep: %d\n", rules->time_to_sleep);
	printf("Number of time to eat: %d\n", rules->must_eat);
	printf("--------------RULE CHECKER:-----------------------------------------\n");
}

void	print_check_philos(t_philo *philos, t_rules *rules)
{
	int	n_philos;
	int	i;

	i = 0;
	n_philos = rules->num_of_philos;
	printf("-----------PHILO CHECK---------------------------------------------\n");
	while (i < n_philos)
	{
		printf("ID: %d\n", philos[i].id);
		printf("Hungry: %d\n", philos[i].hungry);
		printf("Last meal: %ld\n", philos[i].l_meal);
		printf("left fork: %p\n", philos[i].l_fork);
		printf("Right fork: %p\n", philos[i].r_fork);
		printf("\n");
		i++;
	}
	printf("-----------PHILO CHECK---------------------------------------------\n");

}

void	print_check_table(t_table *table)
{
	printf("-----------TABLE CHECK---------------------------------------------\n");
	printf("Num of philos: %d\n", table->philos->rules->num_of_philos);
	printf("Num of forks: %d\n", table->philos->rules->num_of_philos);
	printf("Start Simulation: %ld\n", table->start_sim);
	printf("End sim: %d\n", table->end_sim);
	printf("State adress: %p\n", (void *)&table->state);
	printf("Print address: %p\n", (void *)&table->print);
	printf("-----------TABLE CHECK---------------------------------------------\n");

}

void	cleanup_table(t_table *table, t_rules *rules)
{
	int				i;
	int				n_philos;

	i = 0;
	if (!table)
		return ;
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
	if (rules)
		free(rules);
	if (table)
		free(table);
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
	print_check_rules(rules);
	print_check_philos(table->philos, rules);
	print_check_table(table);
	cleanup_table(table, rules);
	return (0);
}
