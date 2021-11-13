/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:52:44 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/13 18:11:11 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/*
	Norminette sometimes...
*/
int	are_nums_valid(char **argv, int len)
{
	long long	num;
	int			i;
	char		*error_msg;

	error_msg = "Number of required philosophers needs to be greater than 0\n";
	i = 0;
	while (argv && argv[i] != NULL && i < len)
	{
		num = ft_atoi(argv[i]);
		if (i == 0 && num == 0)
			return (print_and_quit(error_msg));
		i++;
	}
	return (0);
}

int	are_args_valid(char **argv, int len)
{
	int		i;
	int		j;
	char	*error_msg;

	error_msg = "Invalid arguments: Please enter whole numbers";
	i = 0;
	while (argv && i < len && argv[i] != NULL)
	{
		j = 0;
		if (argv[i][j] == '\0')
			return (1);
		while (argv[i][j] != '\0')
		{
			if (!(ft_isdigit(argv[i][j])) && argv[i][j] != ' ')
				return (print_and_quit(error_msg));
			j++;
		}
		i++;
	}
	return (are_nums_valid(argv, len));
}
