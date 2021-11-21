/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:45:20 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/19 23:11:42 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	free_and_destroy(t_arthur **arthurs)
{
	t_data	*data;
	int		i;

	usleep(100);
	i = 0;
	data = arthurs[0]->data;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->waiting_line);
	while (i < data->arthur_num)
	{
		pthread_mutex_destroy((*arthurs)[i].own_fork);
		free((*arthurs)[i].own_fork);
		i++;
	}
	free(*arthurs);
	return (0);
}

int	unlock_and_stop(t_arthur *arthur)
{
	pthread_mutex_unlock(arthur->neighbour_fork);
	pthread_mutex_unlock(arthur->own_fork);
	return (1);
}

int	unlock_single_and_stop(t_arthur *arthur)
{
	pthread_mutex_unlock(arthur->own_fork);
	return (1);
}

int	handle_single_arthur(t_arthur *arthur, t_data *data, int id)
{
	printf("%lld %d has taken a fork\n",
		wie_spat_ist_es() - data->start_time, id);
	usleep(data->min_lifetime * 1000);
	return (unlock_single_and_stop(arthur));
}
