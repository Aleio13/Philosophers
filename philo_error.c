/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:09:10 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/11 02:39:14 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	invalid_msg(void)
{
	printf("Error: invalid input\n");
}

void	error_msg(char *msg, t_table *table)
{
	printf("Error: %s\n", msg);
	cleanup_table(table, table->philos->rules);
	exit(2);
}

void	wrong_args(void)
{
	printf("Invalid Arguments\n");
	printf("Please enter the following\n");
	printf("1. Number of Philo <= 200\n");
	printf("2. Time to die in ms > 60\n");
	printf("3. Time to eat in ms > 60\n ");
	printf("4. Time to sleep in ms > 60\n");
	printf("Optional: Number of times philosopers must eat\n");
}
