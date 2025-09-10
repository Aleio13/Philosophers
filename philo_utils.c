/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:47:25 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/10 23:52:08 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	nbr;
	long	count;

	i = 0;
	nbr = 0;
	count = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			count = count * -1;
		i++;
	}
	if (str[i] == '\0')
		return (2147483648);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10;
		nbr += str[i] - '0';
		i++;
	}
	return (nbr * count);
}

long	get_time(void)
{
	long			time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	time = tv.tv_sec * (long)1000 + (tv.tv_usec / (long)1000);
	return ((long)time);
}

int	ft_isdigit(int i)
{
	if ((i >= '0' && i <= '9'))
		return (1);
	return (0);
}

int	ft_sleep(long ms)
{
	long	start;

	start = get_time();
	if (start < 0)
		return (0);
	while (get_time() - start <= ms)
		usleep(100);
	return (1);
}

int	check_all_philos(t_table *table, t_rules *rules)
{
	int	i;
	int	ate;

	ate = 1;
	i = -1;
	while (++i < rules->num_of_philos)
	{
		pthread_mutex_lock(&table->state);
		if (table->philos->n_meals < rules->must_eat)
			ate = 0;
		pthread_mutex_unlock(&table->state);
		if (!check_philo(&table->philos[i], table))
			return (0);
		if (should_end(table))
			return (-1);
	}
	if (rules->must_eat > 0 && ate)
	{
		pthread_mutex_lock(&table->state);
		table->end_sim = 1;
		pthread_mutex_unlock(&table->state);
		return (1);
	}
	return (0);
}
