/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:44:00 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/09 18:22:40 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ll_intersect(t_vec *ray, t_vec wall)
{
	double	t;
	double	u;

	if (!((ray->start.x - ray->end.x) * (wall.start.y - wall.end.y) -
		(ray->start.y - ray->end.y) * (wall.start.x - wall.end.x)))
		return (FALSE);
	t = (((ray->start.x - wall.start.x) * (wall.start.y - wall.end.y) -
		(ray->start.y - wall.start.y) * (wall.start.x - wall.end.x)) /
		((ray->start.x - ray->end.x) * (wall.start.y - wall.end.y) -
		(ray->start.y - ray->end.y) * (wall.start.x - wall.end.x)));
	if (t >= 0 && t <= 1)
	{
		u = -(((ray->start.x - ray->end.x) * (ray->start.y - wall.start.y) -
			(ray->start.y - ray->end.y) * (ray->start.x - wall.start.x)) /
			((ray->start.x - ray->end.x) * (wall.start.y - wall.end.y) -
			(ray->start.y - ray->end.y) * (wall.start.x - wall.end.x)));
		if (u >= 0 && u <= 1)
		{
			ray->end.x = ray->start.x + t * (ray->end.x - ray->start.x);
			ray->end.y = ray->start.y + t * (ray->end.y - ray->start.y);
			return (TRUE);
		}
	}
	return (FALSE);
}

int			ray_cast(t_vec *ray, t_wall *wall)
{
	t_wall	*wall_buf;
	int		counter;

	wall_buf = wall;
	counter = 0;
	while (wall_buf)
	{
		counter += ll_intersect(ray, wall_buf->vec);
		wall_buf = (t_wall *)wall_buf->next_wall;
	}
	return (counter);
}

void		rays_casting(t_ray *ray, t_cub *cub, t_map *map, int count_rays)
{
	double	pow;
	int		i;

	pow = pow_turn(0, map->player->pow + (PLAYER_FOW / 2), 0, 360);
	i = -1;
	while (++i < count_rays)
	{
		ray[i].pow = pow;
		ray[i].vec = make_vector(map->player->pos.x, map->player->pos.y,
			map->player->pos.x + (map->res.x + map->res.y) * sin(ft_rad(pow)),
			map->player->pos.y + (map->res.x + map->res.y) * cos(ft_rad(pow)));
		if (ray_cast(&ray[i].vec, map->walls->north))
			ray[i].wall = 'N';
		if (ray_cast(&ray[i].vec, map->walls->south))
			ray[i].wall = 'S';
		if (ray_cast(&ray[i].vec, map->walls->east))
			ray[i].wall = 'E';
		if (ray_cast(&ray[i].vec, map->walls->west))
			ray[i].wall = 'W';
		ray[i].dst = equal_dst(cub->map->player->pos, ray[i].vec.end);
		pow = pow_turn(pow, -map->ray_pow_step, 0, 360);
	}
}

void		ray_init(t_cub *cub, t_map *map)
{
	if (!(map->ray = malloc(sizeof(t_ray) * cub->res.x)))
		print_error(cub, "ERROR malloc");
	map->ray_pow_step = PLAYER_FOW / (double)cub->res.x;
}
