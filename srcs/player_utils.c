/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:11:00 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/07 00:18:11 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	pow_turn(double pow, double turn, double min, double max)
{
	pow += turn;
	if (max < pow)
		pow -= max;
	else if (min > pow)
		pow += max;
	return (pow);
}

double	pow_turn_updown(double pow, double turn)
{
	pow += turn;
	if (180 < pow)
		pow = 180;
	else if (0 > pow)
		pow = 0;
	return (pow);
}

int		player_cam_y(int res_y, double player_pow_y)
{
	return (res_y * (player_pow_y / 90 - 1));
}
