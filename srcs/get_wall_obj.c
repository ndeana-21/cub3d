/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:39:41 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 03:24:28 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_wall			*horizontal_wall_init(t_map *map, t_wall *wall, double plus_y)
{
	t_wall	*new_wall;
	t_wall	*current_wall;
	t_point	point;

	point.y = 0;
	while (point.y < map->res.y)
	{
		point.x = 0;
		while (point.x < map->res.x)
		{

		}
	}
	return (new_wall);
}

t_wall			*vertical_wall_init(t_wall *wall, double plus_x)
{
	t_wall	*new_wall;

}

t_walls			*raw_to_obj_walls(t_map *map)
{
	t_walls		*walls;

	if (!(walls = malloc(sizeof(t_walls))))
		return (walls);
	
	return (walls);
}

t_sprites		*raw_to_obj_sprite(t_map *map)
{
	t_sprites	*sprites;
	t_sprites	*sprites_start;
	t_point		pos;

	pos.y = 0;
	if (!(sprites_start = (sprites = malloc(sizeof(t_sprites)))))
		return (NULL);
	while (pos.y < (double)map->res.y)
	{
		pos.x = 0;
		while (pos.x < (double)map->res.x)
		{
			if (ft_strchr(SPRITES, map->map[(int)pos.y][(int)pos.x]))
			{
				if (!(sprites->img = find_img(map->img->path, SPRITE_SAMPLE)))
					return (free_sprites(sprites_start));
				sprites->coord = make_point(pos.x + 0.5, pos.y + 0.5);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (sprites_start);
}
