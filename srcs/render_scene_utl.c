/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_utl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 00:53:01 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/14 01:23:46 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				get_pix_wall(t_img *img, t_ray ray, double ratio_y)
{
	double	tmp;
	double	ratio_x;
	t_point	point;

	ratio_x = 0;
	point = (t_point){0, 0};
	if (ray.wall == 'N' || ray.wall == 'S')
		ratio_x = modf(ray.vec.end.x, &tmp);
	else if (ray.wall == 'E' || ray.wall == 'W')
		ratio_x = modf(ray.vec.end.y, &tmp);
	point.x = (double)img->x * ratio_x;
	point.y = (double)img->y * ratio_y;
	return (my_mlx_pixel_get(img->data, point.x, point.y));
}

void			sort_sprite(t_sprite *spr, t_point point)
{
	t_res		res;
	t_sprite	tmp;
	int			i;

	i = -1;
	while (spr[++i].dst != -1)
		spr[i].dst = equal_dst(spr[i].coord, point);
	if (i < 2)
		return ;
	res.y = 0;
	while (++res.y < i)
	{
		res.x = res.y - 1;
		if (spr[res.x].dst < spr[res.y].dst)
			while (res.x >= 0 && (spr[res.x].dst < spr[res.x + 1].dst))
			{
				tmp = spr[res.x];
				spr[res.x] = spr[res.x + 1];
				spr[res.x + 1] = tmp;
				res.x--;
			}
	}
}

int				get_spr_win_pos(t_player player, t_cub *cub, t_sprite spr)
{
	int		pos;
	double	pow;

	if (player.pow > 270 && spr.pow < 90)
		pow = (spr.pow + 360) - player.pow;
	else if (spr.pow > 270 && player.pow < 90)
		pow = spr.pow - (player.pow + 360);
	else
		pow = spr.pow - player.pow;
	pos = (cub->res.x / 2) - (((double)cub->res.x / PLAYER_FOW) * (pow));
	return (pos);
}

void			paint_sprite(t_ray *ray, t_cub *cub, t_sprite spr, t_img *img)
{
	t_res	lim;
	t_res	cur;
	int		mid;
	int		color;

	mid = get_spr_win_pos(*cub->map->player, cub, spr);
	lim = (t_res){mid - (spr.wide / 2), mid + (spr.wide / 2)};
	cur.x = lim.x >= 0 ? lim.x - 1 : -1;
	while (++cur.x < lim.y)
		if ((cur.x < cub->res.x) && ray[cur.x].dst > spr.dst && spr.dst > 0.2)
		{
			cur.y = spr.start_pnt - 1;
			while (++cur.y < (spr.start_pnt + spr.hight))
				if (cur.y < cub->res.y && cur.y >= 0)
				{
					color = my_mlx_pixel_get(img->data,
					img->x * ((double)abs(lim.x - cur.x) / spr.wide),
					img->y * ((double)abs(spr.start_pnt - cur.y) / spr.hight));
					if (color != BLANK_SPRITE)
						my_mlx_pixel_put(cub->data, cur.x, cur.y, color);
				}
		}
}

double			anti_fisheye(double player, double ray)
{
	return (cos(ft_rad(player - ray)));
}
