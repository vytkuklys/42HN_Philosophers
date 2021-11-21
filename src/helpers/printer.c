/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:49:33 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/17 16:56:54 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	print_status(t_data *data, char *action, long long id, int flag)
{
	if (data->all_arthurs_alive == 0)
		return ;
	pthread_mutex_lock(&data->mutex);
	if (data->all_arthurs_alive == 1)
	{
		printf("%lld %lld %s\n", wie_spat_ist_es() - data->start_time,
			id, action);
		data->all_arthurs_alive = flag;
	}
	pthread_mutex_unlock(&data->mutex);
}

int	get_random(void)
{
	struct timeval	time;
	int				random;

	gettimeofday(&time, NULL);
	random = time.tv_sec % 7;
	return (random);
}

void	post_mortem(void)
{
	int	random;

	random = get_random();
	write(1, "\nArthur - ", 11);
	if (random == 1)
		write(1, "”One should use common words to say uncommon things.”\n", 59);
	else if (random == 2)
		write(1,
			"“Animals hear about death for the first time when they die.”\n",
			66);
	else if (random == 3)
		write(1, "”Life is a constant process of dying.”\n", 44);
	else if (random == 4)
		write(1, "”Change alone is eternal, perpetual, immortal.”\n", 53);
	else if (random == 5)
		write(1, "“Each day is a little life.”\n", 34);
	else if (random == 6)
		write(1, "”Reading is thinking with someone else's head ", 49);
	else if (!random)
		write(1,
			"”After your death you will be what you were before your birth.”\n",
			69);
	if (random == 6)
		write(1, "instead of ones own.”\n", 25);
}
