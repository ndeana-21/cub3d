/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 00:45:27 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/09 19:51:49 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			save_bmp(t_cub *cub)
{
	int		**buf;
	t_res	cord;

	if (!(buf = (int **)ft_mda(sizeof(int), cub->res.x, cub->res.y)))
		print_error(cub, "ERROR malloc");
	cord.y = -1;
	while (++cord.y < cub->res.y)
	{
		cord.x = -1;
		while (++cord.x < cub->res.x)
			buf[cord.y][cord.x] = my_mlx_pixel_get(cub->data, cord.x, cord.y);
	}
	create_bmpfile("screen.bmp", cub->res.x, cub->res.y, buf);
	exit(0);
}
