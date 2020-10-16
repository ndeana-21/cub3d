/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 00:50:55 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/16 19:11:26 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			render_sprite(t_ray *ray, t_cub *cub, t_sprites *sprites)
{
	int		i;

	sort_sprite(sprites->spr, cub->map->player->pos);
	i = -1;
	while (sprites->spr[++i].dst != -1)
	{
		sprites->spr[i].pow = ft_deg_of_vec(
			cub->map->player->pos, sprites->spr[i].coord, sprites->spr[i].dst);
		sprites->spr[i].hight = (double)cub->res.y / (sprites->spr[i].dst);
		sprites->spr[i].wide = sprites->spr[i].hight *
			((double)sprites->img->y / (double)sprites->img->x);
		sprites->spr[i].start_pnt = (cub->res.y - sprites->spr[i].hight) / 2 +
			player_cam_y(cub->res.y, cub->map->player->pow_y);
		paint_sprite(ray, cub, sprites->spr[i], sprites->img);
	}
}

void			render_wall(t_ray ray, t_cub *cub,
							t_res xy, t_walls wl)
{
	int		start;
	int		wall;

	wall = cub->res.y / (ray.dst * anti_fisheye(
		cub->map->player->pow, ray.pow));
	start = (cub->res.y - wall) / 2 +
		player_cam_y(cub->res.y, cub->map->player->pow_y);
	xy.y = start > 0 ? start : -1;
	while (++xy.y < (start + wall) && xy.y < cub->res.y)
		if (xy.y < cub->res.y && xy.y >= 0)
		{
			if (ray.wall == 'N')
				my_mlx_pixel_put(cub->data, xy.x, xy.y,
				get_pix_wall(wl.img_n, ray, (double)(xy.y - start) / wall));
			else if (ray.wall == 'S')
				my_mlx_pixel_put(cub->data, xy.x, xy.y,
				get_pix_wall(wl.img_s, ray, (double)(xy.y - start) / wall));
			else if (ray.wall == 'W')
				my_mlx_pixel_put(cub->data, xy.x, xy.y,
				get_pix_wall(wl.img_w, ray, (double)(xy.y - start) / wall));
			else if (ray.wall == 'E')
				my_mlx_pixel_put(cub->data, xy.x, xy.y,
				get_pix_wall(wl.img_e, ray, (double)(xy.y - start) / wall));
		}
}

void			render_cf(t_ray ray, t_cub *cub, t_res point)
{
	int		max_cel;

	max_cel = ((cub->res.y - (cub->res.y / (ray.dst * anti_fisheye(
		cub->map->player->pow, ray.pow)))) / 2) +
		player_cam_y(cub->res.y, cub->map->player->pow_y);
	max_cel = max_cel < cub->res.y ? max_cel + 2 : cub->res.y;
	while (++point.y < max_cel)
		my_mlx_pixel_put(cub->data, point.x, point.y,
			cub->map->walls->celling);
	point.y = max_cel + (cub->res.y / ray.dst) - 3;
	point.y = point.y >= 0 ? point.y : 0;
	while (++point.y < cub->res.y)
		my_mlx_pixel_put(cub->data, point.x, point.y,
			cub->map->walls->floor);
}

static void		minimap_player(t_map *map, t_cub *cub, int scale)
{
	int		i;
	t_ray	*ray;

	i = -1;
	ray = map->ray;
	while (++i < cub->res.x)
		paint_line(cub, create_trgb(0, 255, 100, 100), make_vector(
			ray[i].vec.start.x * scale, ray[i].vec.start.y * scale,
			ray[i].vec.end.x * scale, ray[i].vec.end.y * scale));
	i = -1;
	while (map->sprite->spr[++i].dst != -1)
		paint_circle(cub, create_trgb(0, 255, 255, 0), (t_point){
				map->sprite->spr[i].coord.x * scale,
				map->sprite->spr[i].coord.y * scale}, scale / 2);
	paint_circle(cub, create_trgb(0, 0, 255, 0), (t_point){
		map->player->pos.x * scale, map->player->pos.y * scale}, scale / 2);
}

t_vec			vec_scale(t_vec vec, int scale)
{
	vec.start.x *= scale;
	vec.start.y *= scale;
	vec.end.x *= scale;
	vec.end.y *= scale;
	return (vec);
}

void			minimap(t_map *map, t_cub *cub)
{
	t_point	coord;
	int		scale;

	coord.y = -1;
	scale = cub->res.y / map->res.y / 3;
	while (++coord.y < map->res.y)
	{
		coord.x = -1;
		while (++coord.x < map->res.x)
			if (map->map[(int)coord.y][(int)coord.x] == '1')
				paint_square(cub, create_trgb(0, 255, 255, 255), coord, scale);
			else
				paint_square(cub, create_trgb(0, 0, 0, 0), coord, scale);
	}
	t_wall	*wall = map->walls->north;
	while (wall)
	{
		paint_line(cub, create_trgb(0, 0, 0, 255), vec_scale(wall->vec, scale));
		wall = (t_wall *)wall->next_wall;
	}
	wall = map->walls->south;
	while (wall)
	{
		paint_line(cub, create_trgb(0, 255, 0, 0), vec_scale(wall->vec, scale));
		wall = (t_wall *)wall->next_wall;
	}
	wall = map->walls->east;
	while (wall)
	{
		paint_line(cub, create_trgb(0, 0, 255, 0), vec_scale(wall->vec, scale));
		wall = (t_wall *)wall->next_wall;
	}
	wall = map->walls->west;
	while (wall)
	{
		paint_line(cub, create_trgb(0, 255, 0, 255), vec_scale(wall->vec, scale));
		wall = (t_wall *)wall->next_wall;
	}
	minimap_player(cub->map, cub, scale);
}
