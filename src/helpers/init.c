/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:47:30 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/20 00:26:44 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	is_last_arthur(long long nth, long long total)
{
	return (nth == total);
}

int	init_neighbour_forks(t_arthur **arthurs, long long num)
{
	long long	i;

	i = 0;
	while (i < num)
	{		
		if (is_last_arthur(i + 1, num))
			(*arthurs)[i].neighbour_fork = (*arthurs)[0].own_fork;
		else if (num > 1)
			(*arthurs)[i].neighbour_fork = (*arthurs)[i + 1].own_fork;
		i++;
	}
	return (0);
}

int	init_arthurs(t_arthur **arthurs, t_data *data)
{
	long long	i;

	i = 0;
	while (i < data->arthur_num)
	{
		(*arthurs)[i].dead = 0;
		(*arthurs)[i].id = i + 1;
		(*arthurs)[i].data = data;
		(*arthurs)[i].start_time = wie_spat_ist_es();
		(*arthurs)[i].total_meals = 0;
		(*arthurs)[i].own_fork
			= (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if ((*arthurs)[i].own_fork == NULL)
			return (free_arthurs(arthurs, --i, 1));
		if (pthread_mutex_init((*arthurs)[i].own_fork, NULL) != 0)
			return (destroy_mutexes(arthurs, i));
		i++;
	}
	init_neighbour_forks(arthurs, data->arthur_num);
	return (0);
}

int	init_data_mutex(t_data **data)
{
	if (pthread_mutex_init(&(*data)->mutex, NULL) != 0)
		return (print_and_quit("Failed to initialize a mutex\n"));
	if (pthread_mutex_init(&(*data)->death, NULL) != 0)
		return (destroy_mutex(&(*data)->mutex, NULL));
	if (pthread_mutex_init(&(*data)->waiting_line, NULL) != 0)
		return (destroy_mutex(&(*data)->mutex, &(*data)->death));
	return (0);
}

int	init_data(t_data *data, char **argv, int size)
{
	data->meals_num = -1;
	data->arthur_num = ft_atoi(argv[0]);
	data->min_lifetime = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[2]);
	data->sleep_time = ft_atoi(argv[3]);
	if (size == 5)
		data->meals_num = ft_atoi(argv[4]);
	if (data->min_lifetime == 0)
		write(1, "0 1 died", 9);
	if (data->meals_num == 0 || data->min_lifetime == 0
		|| init_data_mutex(&data))
		return (1);
	data->all_arthurs_alive = 1;
	data->waiting = 0;
	if (data->min_lifetime > 10)
		data->usleep_time = 10000;
	else
		data->usleep_time = 5000;
	data->start_time = wie_spat_ist_es();
	return (0);
}
