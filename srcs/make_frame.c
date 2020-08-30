/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:21:20 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/29 16:47:21 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		add_ceilling(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		num_sample;

	if (0 > (num_sample = find_sample(cub3d->map->texture->name_trgb, "C ")))
		return (print_error("ERROR Have no ceilling\n"));
	y = 0;
	while (y < (cub3d->res_y / 2))
	{
		x = 0;
		while (x < cub3d->res_x)
		{
			my_mlx_pixel_put(cub3d->data, x, y, cub3d->map->texture->trgb[num_sample]);
			x++;
		}
		y++;
	}
	return (1);
}

int		add_floor(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		num_sample;

	if (0 > (num_sample = find_sample(cub3d->map->texture->name_trgb, "F ")))
		return (print_error("ERROR Have no floor\n"));
	y = cub3d->res_y;
	while (y >= (cub3d->res_y / 2))
	{
		x = 0;
		while (x < cub3d->res_x)
		{
			my_mlx_pixel_put(cub3d->data, x, y, cub3d->map->texture->trgb[num_sample]);
			x++;
		}
		y--;
	}
	return (1);
}

int		render_next_frame(t_cub3d *cub3d)
{
	add_ceilling(cub3d);
	add_floor(cub3d);

	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->data->img, 0, 0);
}