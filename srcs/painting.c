/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:37:31 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/06 02:30:38 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			paint_rectangle(t_cub *cub, int trgb,
							t_res start, t_res end)
{
	t_res	pixel;

	pixel.y = start.y;
	while ((pixel.y < end.y) && (pixel.y < cub->res.y))
	{
		pixel.x = start.x;
		while ((pixel.x < end.x) && (pixel.y < cub->res.y))
		{
			my_mlx_pixel_put(cub->data, pixel.x, pixel.y, trgb);
			pixel.x++;
		}
		pixel.y++;
	}
}

void			paint_line(t_cub *cub, int trgb, t_vec vec)
{
	t_point	curent;
	double	dist;
	double	dx;
	double	dy;
	int		i;

	dist = abs((int)(vec.end.x - vec.start.x)) +
		abs((int)(vec.end.y - vec.start.y));
	dx = (vec.end.x - vec.start.x) / dist;
	dy = (vec.end.y - vec.start.y) / dist;
	i = 0;
	while (i <= ceil(dist))
	{
		curent.x = floor(vec.start.x + dx * i);
		curent.y = floor(vec.start.y + dy * i);
		if (curent.x >= 0 && curent.y >= 0 &&
			curent.x < cub->res.x && curent.y < cub->res.y)
			my_mlx_pixel_put(cub->data, curent.x, curent.y, trgb);
		i++;
	}
}

void			paint_square(t_cub *cub, int trgb, t_point coord, int scale)
{
	int		i;
	int		j;

	j = coord.y * scale;
	while (j < ((coord.y + 1) * scale))
	{
		if (j >= cub->res.y)
			break ;
		i = coord.x * scale;
		while (i < ((coord.x + 1) * scale))
		{
			if (i >= cub->res.x)
				break ;
			my_mlx_pixel_put(cub->data, i, j, trgb);
			i++;
		}
		j++;
	}
}

void			paint_circle(t_cub *cub, int trgb, t_point coord, int scale)
{
	t_point	curent;

	curent.y = (coord.y - scale) > 0 ? coord.y - scale : 0;
	while (curent.y < (coord.y + scale))
	{
		if (curent.y >= (double)cub->res.y)
			break ;
		curent.x = (coord.x - scale) > 0 ? coord.x - scale : 0;
		while (curent.x < (coord.x + scale))
		{
			if (curent.x >= (double)cub->res.x)
				break ;
			if (sqrt(pow(abs((int)(curent.x - coord.x)), 2) +
					pow(abs((int)(curent.y - coord.y)), 2)) < scale)
				my_mlx_pixel_put(cub->data, curent.x, curent.y, trgb);
			curent.x++;
		}
		curent.y++;
	}
}
