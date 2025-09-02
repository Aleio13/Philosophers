/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:48:08 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/02 17:55:16 by almatsch         ###   ########.fr       */
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
	if (check < INT_MIN || check > INT_MAX)
		return (0);
	return (1);
}
