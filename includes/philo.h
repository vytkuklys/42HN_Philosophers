/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:53:38 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/13 17:56:54 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data{
	long long		eat_time;
	long long		sleep_time;
	long long		min_lifetime;
	long long		arthur_num;
	long long		meals_num;
	long long		start_time;
	long long		all_arthurs_alive;
	pthread_mutex_t	death;
	pthread_mutex_t	mutex;
}			t_data;

typedef struct s_arthur{
	long long		id;
	int				first_meal;
	pthread_t		th;
	t_data			*data;
	pthread_mutex_t	*own_fork;
	pthread_mutex_t	*neighbour_fork;
}				t_arthur;

void		*ft_calloc(unsigned int num, unsigned int size);
int			are_args_valid(char **argv, int len);
int			ft_strlen(const char *str);
long long	ft_atoi(const char *str);
int			print_and_quit(char *s);
int			ft_isdigit(int arg);
int			are_args_valid(char **argv, int len);
long long	wie_spat_ist_es(void);
int			init_data(t_data *data, char **argv, int size);
int			is_arthur_alive(t_data *data, long long num, int id,
				int *first_meal);
void		print_status(t_data *data, long long now, char *action,
				long long id);
int			init_arthurs(t_arthur **arthurs, t_data *data);
int			init_neighbour_forks(t_arthur **arthurs, long long num);
int			prepare_routine(t_arthur **arthurs);
int			free_and_destroy(t_arthur **arthurs);
int			unlock_and_stop(t_arthur *arthur);
int			unlock_single_and_stop(t_arthur *arthur);
void		post_mortem(void);
int			handle_single_arthur(t_arthur *arthur, t_data *data, int id);
int			join_pthreads(t_arthur **arthurs, int i);
int			free_arthurs(t_arthur **arthurs, int i, int flag);
int			destroy_mutex(pthread_mutex_t	*mutex);
int			destroy_mutexes(t_arthur **arthurs, int i);
int			eating(t_arthur *arthur, t_data *data, int id);

#endif
