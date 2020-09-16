/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 04:44:34 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 00:25:21 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	set_r(int trgb, int r)
{
	return (trgb | (r << 16));
}

int	set_g(int trgb, int g)
{
	return (trgb | (g << 8));
}

int	set_b(int trgb, int b)
{
	return (trgb | b);
}
