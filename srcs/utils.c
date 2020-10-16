/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 19:10:08 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/07 00:14:40 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			*check_sample(char *sample, char *str)
{
	while (*sample && *str)
	{
		if (*sample != *str)
			return (0);
		str++;
		sample++;
	}
	return (str);
}

t_vec			make_vector(double x1, double y1, double x2, double y2)
{
	t_vec	vec;

	vec.start.x = x1;
	vec.start.y = y1;
	vec.end.x = x2;
	vec.end.y = y2;
	return (vec);
}

double			equal_dst(t_point player, t_point pos)
{
	return (sqrt(pow(player.x - pos.x, 2) + pow(player.y - pos.y, 2)));
}

double			ft_deg_of_vec(t_point from, t_point to, double dst)
{
	double	s_deg;

	if (from.x - to.x > 0)
		s_deg = 180 + ft_deg(acos((from.y - to.y) / dst));
	else
		s_deg = ft_deg(acos((to.y - from.y) / dst));
	return (s_deg);
}

double			ft_mod(double num)
{
	return (num - floor(num));
}
