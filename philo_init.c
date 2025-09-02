/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:38:37 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/02 18:19:36 by almatsch         ###   ########.fr       */
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
	return (rules);
}

t_table	*init_table(t_rules *rules)
{
	t_table			*table;

	table = malloc(sizeof(t_table));
	table->forks = malloc(sizeof(pthread_mutex_t) * rules->num_of_philos);
	if (!table->forks)
		return (NULL);
	table->philos = //TODO init_philo function proto: init_philo(t_rules *rules, pthread_mutex_t *forks);
	table->end_sim  = 0;
	pthread_mutex_init(&table->p_lock, NULL);
}
