/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:44:00 by ndeana            #+#    #+#             */
/*   Updated: 2020/09/16 01:40:43 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ll_intersect(t_vec *ray, t_vec wall)
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
	u = - (((ray->start.x - ray->end.x) * (ray->start.y - wall.start.y) -
		(ray->start.y - ray->end.y) * (ray->start.x - wall.start.x)) /
		((ray->start.x - ray->end.x) * (wall.start.y - wall.end.y) -
		(ray->start.y - ray->end.y) * (wall.start.x - wall.end.x)));
	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		ray->end.x = ray->start.x + t * (ray->end.x - ray->start.x);
		ray->end.y = ray->start.y + t * (ray->end.y - ray->start.y);
		return (TRUE);
	}
	return (FALSE);
}

t_vec			ray_cast(t_wall *wall, t_point pos, t_res max, double pow)
{
	t_vec	ray;
	t_wall	*wall_buf;

	ray.start.x = pos.x;
	ray.start.y = pos.y;
	ray.end.x = pos.x + (max.x + max.y) * sin(rad(pow));
	ray.end.y = pos.y + (max.x + max.y) * cos(rad(pow));
	wall_buf = wall;
	while (wall_buf)
	{
		ll_intersect(&ray, wall_buf->vec);
		wall_buf = wall_buf->next_wall;
	}
	return (ray);
}

t_ray			*rays_casting(t_ray *rays, t_walls *walls,
								t_player player, t_cub *cub)
{
	t_ray	*ray;

	ray = rays;
	ray->pow = PLAYER_FOW / 2;
	while (ray)
	{
		ray->vec = ray_cast(walls->north, player.pos, cub->map->res, ray->pow);
		ray->vec = ray_cast(walls->south, player.pos, cub->map->res, ray->pow);
		ray->vec = ray_cast(walls->east, player.pos, cub->map->res, ray->pow);
		ray->vec = ray_cast(walls->west, player.pos, cub->map->res, ray->pow);
		ray = ray->next_ray;
		ray->pow = pow_turn(ray->pow, cub->map->ray_pow_step);
	}
	return (rays);
}

t_ray			*ray_init(int count_rays)
{
	t_ray	*ray;
	t_ray	*start_ray;
	int		i;

	if (!(start_ray = malloc(sizeof(t_ray))))
		return (NULL);
	ray = start_ray;
	i = count_rays;
	while (--i > 0)
	{
		if (!(ray->next_ray = malloc(sizeof(t_ray))))
			return (NULL);
		ray = ray->next_ray;
	}
	return (start_ray);
}
