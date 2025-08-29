/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:38:37 by almatsch          #+#    #+#             */
/*   Updated: 2025/08/29 15:18:53 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	is_input_valid(char **arv)
{
	int	i;
	int j;

	i = 0;
	while (arv[i])
	{
		j = 0;
		while (arv[i][j])
		{
			while (arv[i][j] == ' ' || arv[i][j] == '+')
				j++;
			if (!ft_isdigit((int)arv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_rules	*init_rules(int arc, char **arv)
{
	t_rules	*rules;

	if (!is_input_valid)
		return (invalid_msg(), NULL);
	rules->num_of_philos = ft_atoi(arv[1]);
	rules->time_to_die = ft_atoi(arv[2]);
	rules->time_to_eat = ft_atoi(arv[3]);
	rules->time_to_sleep = ft_atoi(arv[4]);
	if (arc == 6)
		rules->must_eat = ft_atoi(arv[6]);
	else
		rules->must_eat = 0;
	return (rules);
}
