/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_and_quit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:39:22 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/12 22:16:16 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	print_and_quit(char *s)
{
	int	len;

	if (s == NULL)
		return (1);
	len = ft_strlen(s);
	write(2, s, len);
	return (1);
}
