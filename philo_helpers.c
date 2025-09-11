/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:48:08 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/11 02:36:27 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_input_valid(char **arv)
{
	int	i;
	int	j;

	i = 0;
	while (arv[i])
	{
		j = 0;
		while (arv[i][j] && i > 0)
		{
			while (arv[i][j] == ' ' || arv[i][j] == '+')
				j++;
			if (!ft_isdigit((int)arv[i][j]))
				return (0);
			j++;
		}
		if (!check_atol(arv[i]) && i > 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_atol(const char *str)
{
	long	check;

	check = ft_atol(str);
	if (check < INT_MIN || check > 10000)
		return (0);
	return (1);
}

int	print_status(t_philo *philo, t_table *table, char *status)
{
	long	time;

	pthread_mutex_lock(&table->print);
	time = get_time() - table->start_sim;
	printf("%ld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&table->print);
	return (1);
}

int	should_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->state);
	end = table->end_sim;
	pthread_mutex_unlock(&table->state);
	return (end);
}

int	check_philo(t_philo *philo, t_table *table)
{
	t_rules	*rules;
	long	time;

	rules = philo->rules;
	time = get_time();
	if (time < 0)
		error_msg("get_time failed", table);
	pthread_mutex_lock(&table->state);
	if (time - philo->l_meal > rules->time_to_die)
	{
		table->end_sim = 1;
		pthread_mutex_unlock(&table->state);
		print_status(philo, table, "that dude died bruh !");
		return (0);
	}
	pthread_mutex_unlock(&table->state);
	return (1);
}
