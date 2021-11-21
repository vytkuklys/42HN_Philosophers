/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:21:34 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/20 00:26:27 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	thinking(t_data *data, int id)
{
	usleep(100);
	if (data->all_arthurs_alive == 0)
		return (1);
	print_status(data, "is thinking", id, 1);
	return (0);
}

int	eating(t_arthur **arthur, t_data **data, int id)
{
	long long	before;
	long long	now;

	print_status(*data, "is eating", id, 1);
	before = wie_spat_ist_es();
	(*arthur)->start_time = wie_spat_ist_es();
	now = before;
	while ((now - before) < (*data)->eat_time)
	{
		if (!(*data)->all_arthurs_alive)
			return (unlock_and_stop(*arthur));
		usleep(100);
		now = wie_spat_ist_es();
	}
	pthread_mutex_unlock((*arthur)->neighbour_fork);
	pthread_mutex_unlock((*arthur)->own_fork);
	(*arthur)->total_meals++;
	return (0);
}
