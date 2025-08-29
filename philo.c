/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:28:36 by almatsch          #+#    #+#             */
/*   Updated: 2025/08/29 15:12:18 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wrong_args()
{
	printf("Invalid Arguments\n");
	printf("Please enter the following\n");
	printf("1. Number of Philo\n");
	printf("2. Time to die in ms\n");
	printf("3. Time to eat in ms\n");
	printf("4. Time to sleep in ms\n");
	printf("Optional: Number of times philosopers must eat\n");
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
	printf("Check Passed\n");
	return (0);
}
