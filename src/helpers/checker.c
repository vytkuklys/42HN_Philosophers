/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:49:10 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/13 17:13:04 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	is_arthur_alive(t_data *data, long long num, int id, int *first_meal)
{
	long long	duration;

	duration = num;
	if (first_meal != NULL && (*first_meal))
	{
		(*first_meal) = 0;
		duration = wie_spat_ist_es() - data->start_time;
	}
	if (duration >= data->min_lifetime)
	{
		pthread_mutex_lock(&data->death);
		if (data->all_arthurs_alive == 1)
			printf("%lld %d died\n", wie_spat_ist_es() - data->start_time, id);
		data->all_arthurs_alive = 0;
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	return (0);
}
