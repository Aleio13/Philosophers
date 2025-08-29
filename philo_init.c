/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:38:37 by almatsch          #+#    #+#             */
/*   Updated: 2025/08/29 18:13:20 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

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
