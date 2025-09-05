/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almatsch <almatsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:26:28 by almatsch          #+#    #+#             */
/*   Updated: 2025/09/05 19:35:54 by almatsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INT_MIN -2147483648
# define INT_MAX 2147483647
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_table t_table;

typedef struct s_rules
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_philos;
	int		must_eat;
	t_table	*table;
}			t_rules;

typedef struct	s_philo
{
	t_rules			*rules;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			l_meal;
	int				n_meals;
	int				hungry;
	int				id;
}					t_philo;

typedef struct	s_table
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	state;
	long			start_sim;
	int				end_sim;
}					t_table;

t_rules	*init_rules(int arc, char **arv);
t_table	*init_table(t_rules *rules);
t_philo	*init_philo(t_rules *rules, pthread_mutex_t *forks, int n_philo);
int		ft_isdigit(int i);
int		ft_sleep(long ms);
void	*start_routine(void *arg);
long	ft_atol(const	char *str);
long	get_time(void);
int		check_atol(const char *str);
int		check_philo(t_philo *philo, t_table *table);
int		is_input_valid(char **arv);
void	wrong_args();
void	invalid_msg(void);
void	cleanup_table(t_table *table, t_rules *rules);
void	error_msg(char *msg, t_table *table);
void	*start_monitor(void *arg);
void	start_simulation(t_table *table);
int		print_status(t_philo *philo,t_table *table, char *status);
#endif
