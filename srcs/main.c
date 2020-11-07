/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 22:52:08 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/20 12:52:48 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = cub3d_init();
	arg_error(argc, argv, cub);
	parser(cub);
	ray_init(cub, cub->map);
	raw_to_obj_walls(cub, cub->map);
	raw_to_obj_sprite(cub, cub->map, SPRITES);
	render_frame(cub);
	if (cub->save)
		save_bmp(cub);
	if (!(cub->win = mlx_new_window(
					cub->mlx, cub->res.x, cub->res.y, "cub3D")))
		return (print_error(cub, "MLX_ERROR failed to create window"));
	mlx_hook(cub->win, 2, 1L << 0, hook_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, hook_release, cub);
	mlx_hook(cub->win, 6, 1L << 6, hook_mouse_x, cub);
	mlx_hook(cub->win, 17, 1L << 17, close_window, cub);
	mlx_loop_hook(cub->mlx, render_next_frame, cub);
	mlx_loop(cub->mlx);
	return (0);
}
