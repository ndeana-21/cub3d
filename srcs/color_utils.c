/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 04:44:34 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/10 13:00:33 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	set_r(int trgb, int r)
{
	if (r < 0 || r > 255)
		return (-1);
	return (trgb | (r << 16));
}

int	set_g(int trgb, int g)
{
	if (g < 0 || g > 255)
		return (-1);
	return (trgb | (g << 8));
}

int	set_b(int trgb, int b)
{
	if (b < 0 || b > 255)
		return (-1);
	return (trgb | b);
}
