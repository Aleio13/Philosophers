/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:28:36 by almatsch          #+#    #+#             */
/*   Updated: 2025/08/29 18:14:09 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_check(t_rules *rules)
{
	printf("Number of Philo: %d\n", rules->num_of_philos);
	printf("Time of death: %d\n", rules->time_to_die);
	printf("Time to eat: %d\n", rules->time_to_eat);
	printf("time to sleep: %d\n", rules->time_to_sleep);
	printf("Number of time to eat: %d\n", rules->must_eat);
}

int main(int arc, char **arv)
{
	t_rules	*rules;

	if (arc < 5 || arc > 6)
	{
		wrong_args();
		return (1);
	}
	rules = init_rules(arc, arv);
	if (!rules)
		return (1);
	print_check(rules);
	free(rules);
	return (0);
}
