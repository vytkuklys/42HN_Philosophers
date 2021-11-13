/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:35:53 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/12 23:20:34 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_argc_valid(int argc)
{
	if (argc == 5 || argc == 6)
		return (0);
	write(2, "Required arguments: number_of_philosophers time_to_die ", 56);
	write(2, "time_to_eat time_to_sleep\nOptional argument: ", 46);
	write(2, "max_number_of_meals\n", 21);
	return (1);
}

int	main(int argc, char **argv)
{
	t_arthur	*arthurs;
	t_data		data;

	if (is_argc_valid(argc) || are_args_valid(&argv[1], argc - 1))
		return (1);
	if (init_data(&data, &argv[1], argc - 1))
		return (1);
	arthurs = (t_arthur *)malloc(sizeof(t_arthur) * data.arthur_num);
	if (arthurs == NULL || init_arthurs(&arthurs, &data))
		return (1);
	prepare_routine(&arthurs);
	free_and_destroy(&arthurs);
	post_mortem();
	return (0);
}
