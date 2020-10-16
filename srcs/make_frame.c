/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:21:20 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/15 23:10:14 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		render_scene(t_cub *cub, t_ray *ray, t_sprites *sprite)
{
	t_res	point;

	point = (t_res){-1, -1};
	while (++point.x < cub->res.x)
	{
		render_cf(ray[point.x], cub, point);
		render_wall(ray[point.x], cub, point, *cub->map->walls);
	}
	render_sprite(ray, cub, sprite);
	if (cub->keys.m)
		minimap(cub->map, cub);
}

int			render_frame(t_cub *cub)
{
	if (!(cub->data->img = mlx_new_image(cub->mlx, cub->res.x, cub->res.y)))
		print_error(cub, "MLX_ERROR can not create new img");
	if (!(cub->data->addr = mlx_get_data_addr(cub->data->img, &cub->data->bpp,
									&cub->data->line_len, &cub->data->endian)))
		print_error(cub, "MLX_ERROR can not get addr");
	rays_casting(cub->map->ray, cub, cub->map, cub->res.x);
	render_scene(cub, cub->map->ray, cub->map->sprite);
	return (0);
}

int			render_next_frame(t_cub *cub)
{
	if (cub->data->img && cub->mlx)
		mlx_destroy_image(cub->mlx, cub->data->img);
	if (!cub->keys.h && cub->mlx)
		mlx_mouse_show(cub->mlx, cub->win);
	else
	{
		mlx_mouse_hide(cub->mlx, cub->win);
		mlx_mouse_move(cub->mlx, cub->win, cub->res.x / 2, cub->res.y / 2);
		cub->map->player->pow = pow_turn(cub->map->player->pow,
			cub->keys.mouse_x * -(TR_SPEED / 10), 0, 360);
		cub->map->player->pow_y = pow_turn_updown(cub->map->player->pow_y,
			cub->keys.mouse_y * -(TR_SPEED / 6));
	}
	player_keys_move(cub);
	render_frame(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->data->img, 0, 0);
	mlx_do_sync(cub->mlx);
	return (0);
}
