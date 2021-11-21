/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:49:10 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/20 00:25:18 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	are_enough_meals_eaten(t_arthur **arthurs, t_data *data)
{
	long long	meals;
	long long	i;

	if ((*arthurs)[0].total_meals == -1)
		return (1);
	else if (data->eat_time * (2 + (data->arthur_num % 2))
		== data->min_lifetime)
		return (1);
	i = 0;
	meals = 0;
	while (i < data->arthur_num)
	{
		meals += (*arthurs)[i].total_meals;
		i++;
	}
	if (meals / i == data->meals_num)
		return (0);
	return (1);
}

void	death_watch(t_arthur **arthurs, t_data *data)
{
	int	j;
	int	i;

	i = 0;
	usleep(data->usleep_time);
	while (i > -1)
	{
		j = 0;
		while (j < data->arthur_num)
		{
			if (wie_spat_ist_es() - (*arthurs)[j].start_time >=
				data->min_lifetime)
			{
				if (data->meals_num == -1 || are_enough_meals_eaten(arthurs,
						data))
					print_status(data, "died", (*arthurs)[j].id, 0);
				data->all_arthurs_alive = 0;
				i = -3;
				break ;
			}
			usleep(100);
			j++;
		}
		i++;
	}
}
