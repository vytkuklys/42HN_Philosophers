/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:11:18 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/12 23:45:12 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	join_pthreads(t_arthur **arthurs, int i)
{
	while (i >= 0)
	{
		if (pthread_join((*arthurs)[i].th, NULL) != 0)
			return (print_and_quit("Failed to join a thread.\n"));
		i--;
	}
	return (print_and_quit("Failed to create a thread.\n"));
}

int	free_arthurs(t_arthur **arthurs, int i, int flag)
{
	t_data	*data;

	data = arthurs[0]->data;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->death);
	while (i >= 0)
	{
		pthread_mutex_destroy((*arthurs)[i].own_fork);
		free((*arthurs)[i].own_fork);
		i--;
	}
	free(*arthurs);
	if (flag != 0)
		return (print_and_quit("Memory allocation error.\n"));
	return (0);
}

int	destroy_mutex(pthread_mutex_t	*mutex)
{
	pthread_mutex_destroy(mutex);
	return (print_and_quit("Failed to initialize a mutex\n"));
}

int	destroy_mutexes(t_arthur **arthurs, int i)
{
	if (i >= 0)
		free((*arthurs)[i].own_fork);
	i--;
	if (i >= 0)
		free_arthurs(arthurs, i, 0);
	return (print_and_quit("Failed to initialize a mutex\n"));
}
