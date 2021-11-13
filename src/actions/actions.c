/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:47:37 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/13 17:55:33 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	taking_forks(t_arthur *arthur, t_data *data, int id)
{
	pthread_mutex_lock(arthur->own_fork);
	usleep(250);
	if (!data->all_arthurs_alive)
		return (unlock_single_and_stop(arthur));
	print_status(data, wie_spat_ist_es(), "has taken a fork", id);
	if (arthur->neighbour_fork == arthur->own_fork)
		return (handle_single_arthur(arthur, data, id));
	pthread_mutex_lock(arthur->neighbour_fork);
	usleep(250);
	if (!data->all_arthurs_alive)
		return (unlock_and_stop(arthur));
	print_status(data, wie_spat_ist_es(), "has taken a fork", id);
	return (0);
}

int	sleeping(t_data *data, int id)
{
	long long	time;
	long long	before;
	long long	now;

	before = wie_spat_ist_es();
	now = before;
	print_status(data, wie_spat_ist_es(), "is sleeping", id);
	if (data->sleep_time > data->min_lifetime)
		time = data->min_lifetime;
	else
		time = data->sleep_time;
	while ((now - before) < time)
	{
		if (!data->all_arthurs_alive)
			return (1);
		usleep(100);
		now = wie_spat_ist_es();
	}
	return (is_arthur_alive(data, data->sleep_time + data->eat_time, id, NULL));
}

int	thinking(t_data *data, int id)
{
	long long	before;
	long long	now;
	long long	time_used;

	before = wie_spat_ist_es();
	time_used = data->eat_time + data->sleep_time;
	usleep(100);
	now = wie_spat_ist_es();
	return (is_arthur_alive(data, data->sleep_time
			+ data->eat_time + (now - before), id, NULL));
}

void	*start_routine(void *arg)
{
	t_arthur	*arthur;
	t_data		*data;
	long long	meals;

	arthur = (void *)arg;
	data = arthur->data;
	meals = data->meals_num;
	if (arthur->id % 2 == 0)
		usleep(10000);
	while (data->all_arthurs_alive && meals != 0)
	{
		if (!data->all_arthurs_alive || taking_forks(arthur, data, arthur->id))
			break ;
		if (eating(arthur, data, arthur->id))
			break ;
		meals--;
		if (meals == 0)
			break ;
		if (sleeping(data, arthur->id))
			break ;
		if (thinking(data, arthur->id))
			break ;
	}
	return (NULL);
}

int	prepare_routine(t_arthur **arthurs)
{
	t_data		*data;
	long long	i;

	i = 0;
	data = (*arthurs)->data;
	while (i < data->arthur_num)
	{
		if (pthread_create(&(*arthurs)[i].th, NULL,
			&start_routine, &(*arthurs)[i]) != 0)
			return (join_pthreads(arthurs, i));
		i++;
	}
	i = 0;
	while (i < data->arthur_num)
	{
		if (pthread_join((*arthurs)[i].th, NULL) != 0)
			return (print_and_quit("Failed to join a thread.\n"));
		i++;
	}
	return (0);
}
