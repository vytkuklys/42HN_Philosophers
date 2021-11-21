/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:47:37 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/21 23:53:16 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	taking_forks(t_arthur *arthur, t_data *data, int id)
{
	if (data->all_arthurs_alive == 0)
		return (1);
	pthread_mutex_lock(arthur->own_fork);
	if (arthur->neighbour_fork == arthur->own_fork)
		return (handle_single_arthur(arthur, data, id));
	pthread_mutex_lock(arthur->neighbour_fork);
	usleep(200);
	if (data->all_arthurs_alive == 0)
		return (unlock_and_stop(arthur));
	print_status(data, "has taken a fork", id, 1);
	print_status(data, "has taken a fork", id, 1);
	return (0);
}

int	sleeping(t_data **data, int id)
{
	long long	time;
	long long	before;
	long long	now;

	usleep(100);
	if ((*data)->all_arthurs_alive == 1)
		print_status(*data, "is sleeping", id, 1);
	else
		return (1);
	before = wie_spat_ist_es();
	now = before;
	time = (*data)->sleep_time;
	while ((now - before) < time)
	{
		if (!(*data)->all_arthurs_alive)
			return (1);
		usleep(100);
		now = wie_spat_ist_es();
	}
	return (0);
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
		usleep(data->usleep_time);
	while (data->all_arthurs_alive && meals != 0)
	{
		if (!data->all_arthurs_alive || taking_forks(arthur, data, arthur->id))
			break ;
		if (eating(&arthur, &data, arthur->id))
			break ;
		if (meals > 0)
			meals--;
		if (meals == 0 || sleeping(&data, arthur->id))
			break ;
		if (thinking(data, arthur->id))
			break ;
	}
	return (NULL);
}

void	*line_them_up(void *arg)
{
	t_data		*data;
	t_arthur	*arthur;
	long long	i;

	i = 0;
	arthur = (void *)arg;
	data = arthur->data;
	pthread_mutex_lock(&data->waiting_line);
	data->start_time = wie_spat_ist_es();
	data->waiting++;
	pthread_mutex_unlock(&data->waiting_line);
	while (data->waiting != data->arthur_num)
		;
	pthread_mutex_lock(&data->waiting_line);
	arthur->start_time = data->start_time;
	pthread_mutex_unlock(&data->waiting_line);
	start_routine(&(*arthur));
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
			&line_them_up, &(*arthurs)[i]) != 0)
			return (join_pthreads(arthurs, i));
		i++;
	}
	while (data->waiting != data->arthur_num)
		usleep(100);
	death_watch(arthurs, data);
	i = 0;
	while (i < data->arthur_num)
	{
		if (pthread_join((*arthurs)[i].th, NULL) != 0)
			return (print_and_quit("Failed to join a thread.\n"));
		i++;
	}
	return (0);
}
