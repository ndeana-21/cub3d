/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:47:05 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/06 23:25:38 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		colision(t_map *map, t_vec *pos)
{
	if (ray_cast(pos, map->walls->north) ||
		ray_cast(pos, map->walls->south) ||
		ray_cast(pos, map->walls->west) ||
		ray_cast(pos, map->walls->east))
		return (TRUE);
	if (ft_strchr(COLISION, map->map[(int)pos->end.y][(int)pos->end.x]))
		return (TRUE);
	return (FALSE);
}

int		player_move(t_map *map, t_player *player, double pow)
{
	t_player	move;

	pow = pow < 360 ? pow : pow - 360;
	move.pos = player->pos;
	move.pos.x += MV_SPEED * sin(ft_rad(pow));
	move.pos.y += MV_SPEED * cos(ft_rad(pow));
	if (colision(map, &(t_vec){player->pos, move.pos}))
		return (FALSE);
	player->pos = move.pos;
	return (TRUE);
}

int		player_keys_move(t_cub *cub)
{
	t_map	*map;

	map = cub->map;
	if (cub->keys.w || cub->keys.a || cub->keys.s || cub->keys.d ||
		cub->keys.left || cub->keys.right || cub->keys.up || cub->keys.down)
	{
		if (cub->keys.w)
			player_move(map, map->player, map->player->pow);
		if (cub->keys.a)
			player_move(map, map->player, map->player->pow + 90);
		if (cub->keys.s)
			player_move(map, map->player, map->player->pow + 180);
		if (cub->keys.d)
			player_move(map, map->player, map->player->pow + 270);
		if (cub->keys.left)
			map->player->pow = pow_turn(map->player->pow, TR_SPEED, 0, 360);
		if (cub->keys.right)
			map->player->pow = pow_turn(map->player->pow, -TR_SPEED, 0, 360);
		if (cub->keys.up)
			map->player->pow_y = pow_turn_updown(map->player->pow_y, TR_SPEED);
		if (cub->keys.down)
			map->player->pow_y = pow_turn_updown(map->player->pow_y, -TR_SPEED);
		return (1);
	}
	return (0);
}
