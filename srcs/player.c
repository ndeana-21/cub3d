/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:47:05 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 01:41:49 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		colision(t_map *map, t_point pos)
{
	if (ft_strchr(COLISION, map->map[(int)pos.y][(int)pos.x]))
		return (1);
	return (0);
}

double	pow_turn(double pow, double turn)
{
	pow += turn;
	if (360 < pow)
		pow -= 360;
	else if (0 > pow)
		pow += 360;
	return (pow);
}

int		player_move(t_map *map, t_player *player, double pow)
{
	t_player	move;

	pow = pow < 360 ? pow : pow - 360;
	move.pos = player->pos;
	move.pos.x += MV_SPEED * sin(rad(pow));
	move.pos.y += MV_SPEED * cos(rad(pow));
	if (colision(map, move.pos))
		return 0;
	player->pos = move.pos;
	return (1);
}

int		player_keys_move(t_cub *cub)
{
	t_map	*map;

	map = cub->map;
	if (cub->keys.w || cub->keys.a || cub->keys.s || cub->keys.d ||
		cub->keys.q || cub->keys.e)
	{
		if (cub->keys.w)
			player_move(map, map->player, map->player->pow);
		if (cub->keys.a)
			player_move(map, map->player, map->player->pow + 90);
		if (cub->keys.s)
			player_move(map, map->player, map->player->pow + 180);
		if (cub->keys.d)
			player_move(map, map->player, map->player->pow + 270);
		if (cub->keys.q)
			map->player->pow = pow_turn(map->player->pow, TR_SPEED);
		if (cub->keys.e)
			map->player->pow = pow_turn(map->player->pow, -TR_SPEED);
		return (1);
	}
	return (0);
}
