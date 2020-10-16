/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:26:33 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/06 00:02:13 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}

int	get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	add_shade(int trgb, double distance)
{
	int		r;
	int		g;
	int		b;

	r = get_r(trgb);
	g = get_g(trgb);
	b = get_b(trgb);
	r -= r * distance;
	g -= g * distance;
	b -= b * distance;
	return (create_trgb(0, r, g, b));
}
