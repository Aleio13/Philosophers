/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:26:28 by almatsch          #+#    #+#             */
/*   Updated: 2025/08/29 16:57:48 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INT_MIN -2147483648
# define INT_MAX 2147483647
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

typedef struct s_rules
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_philos;
	int	must_eat;
}	t_rules;

typedef struct	s_philo
{
	t_rules	rules;
	int		id;
}	t_philo;

t_rules	*init_rules(int arc, char **arv);
int		ft_isdigit(int i);
long	ft_atol(const	char *str);
int		check_atol(const char *str);
void	wrong_args();
void	invalid_msg(void);
void	print_check(t_rules *rules);

#endif
