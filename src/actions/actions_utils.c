/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:21:34 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/13 17:55:04 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	get_eating_time(t_data *data, int first_meal)
{
	int	delay;

	delay = 0;
	if (first_meal)
	{
		delay = wie_spat_ist_es() - data->start_time;
		if (delay + data->eat_time > data->min_lifetime)
			return (data->min_lifetime - delay);
		else
			return (data->eat_time);
	}
	if (data->eat_time > data->min_lifetime)
		return (data->min_lifetime);
	else
		return (data->eat_time);
}

int	eating(t_arthur *arthur, t_data *data, int id)
{
	long long	before;
	long long	time;
	long long	now;

	before = wie_spat_ist_es();
	now = before;
	print_status(data, wie_spat_ist_es(), "is eating", id);
	time = get_eating_time(data, arthur->first_meal);
	while ((now - before) < time)
	{
		if (!data->all_arthurs_alive)
			return (unlock_and_stop(arthur));
		usleep(100);
		now = wie_spat_ist_es();
	}
	pthread_mutex_unlock(arthur->neighbour_fork);
	pthread_mutex_unlock(arthur->own_fork);
	usleep(100);
	return (is_arthur_alive(data, data->eat_time, id, &arthur->first_meal));
}
