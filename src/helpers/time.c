/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:25:53 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/12 23:44:14 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long long	wie_spat_ist_es(void)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL))
	{
		write(2, "Error ocurred when getting time of the day\n", 44);
		return (-1);
	}
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}
