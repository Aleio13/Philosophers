/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:38:37 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/02 22:18:34 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

t_rules	*init_rules(int arc, char **arv)
{
	t_rules	*rules;

	rules = malloc(sizeof (t_rules));
	if (!rules)
		return (NULL);
	if (!is_input_valid(arv))
		return (invalid_msg(), NULL);
	rules->num_of_philos = ft_atol(arv[1]);
	rules->time_to_die = ft_atol(arv[2]);
	rules->time_to_eat = ft_atol(arv[3]);
	rules->time_to_sleep = ft_atol(arv[4]);
	if (arc == 6)
		rules->must_eat = ft_atol(arv[5]);
	else
		rules->must_eat = -1;
	if (rules->num_of_philos == 0)
		return (invalid_msg(, NULL));
	return (rules);
}

t_table	*init_table(t_rules *rules)
{
	t_table			*table;
	int				i;
	struct timeval	tv;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * rules->num_of_philos);
	if (!table->forks)
		return (NULL);
	i = 0;
	while (i++ < rules->num_of_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	table->philos =
	table->end_sim  = 0;
	table->philos = init_philo(rules, table->forks, rules->num_of_philos);
	table->start_sim = get_time();
	pthread_mutex_init(&table->p_lock, NULL);
	pthread_mutex_init(&table->state, NULL);
	return (table);
}

t_philo	*init_philo(t_rules *rules, pthread_mutex_t *forks, int n_philo)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * n_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < n_philo)
	{
		philos[i].id = i;
		philos[i].n_meals = 0;
		philos[i].rules = rules;
		philos[i].hungry = 1;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % n_philo];
		i++;
	}
}
