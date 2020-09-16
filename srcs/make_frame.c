/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:21:20 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 16:43:43 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			minimap_player(t_map *map, t_cub *cub, int scale)
{
	t_vec 	vector;
	t_wall	wall1;
	t_wall	wall2;
	t_wall	wall3;
	t_wall	wall4;

	wall1.vec = make_vector(0, 0, map->res.x, 0);
	wall2.vec = make_vector(map->res.x, 0, map->res.x, map->res.y);
	wall3.vec = make_vector(map->res.x, map->res.y, 0, map->res.y);
	wall4.vec = make_vector(0, map->res.y, 0, 0);
	
	wall1.next_wall = &wall2;
	wall2.next_wall = &wall3;
	wall3.next_wall = &wall4;
	wall4.next_wall = NULL;
	vector = ray_cast(&wall1, map->player->pos, map->res, map->player->pow);
	vector.start.x = vector.start.x * scale;
	vector.start.y = vector.start.y * scale;
	vector.end.x = vector.end.x * scale;
	vector.end.y = vector.end.y * scale;
	paint_circle(cub, create_trgb(0,0,255,0), vector.start, scale / 2);
	paint_line(cub, create_trgb(0,255,100,100), vector);
}

void			minimap(t_map *map, t_cub *cub, int scale)
{
	t_point	coord;

	coord.y = 0;
	while (coord.y < map->res.y)
	{
		coord.x = 0;
		while (coord.x < map->res.x)
		{
			if (map->map[(int)coord.y][(int)coord.x] == '1')
				paint_square(cub, create_trgb(0, 255, 255, 255), coord, scale);
			else if (map->map[(int)coord.y][(int)coord.x] == '2')
				paint_square(cub, create_trgb(0, 255, 0, 255), coord, scale);
			else
				paint_square(cub, create_trgb(0, 0, 0, 0), coord, scale);
			coord.x++;
		}
		coord.y++;
	}
	minimap_player(cub->map, cub, scale);
}

int		render_next_frame(t_cub *cub)
{
	if (player_keys_move(cub))
	{
		cub->data->img = mlx_new_image(cub->mlx, cub->res.x, cub->res.y);
		cub->data->addr = mlx_get_data_addr(cub->data->img,
											&cub->data->bits_per_pixel,
											&cub->data->line_length,
											&cub->data->endian);
		minimap(cub->map, cub, 20);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->data->img, 0, 0);
		mlx_destroy_image(cub->mlx, cub->data->img);
	}
	return(0);
}