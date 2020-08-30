/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 22:14:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/08/25 22:45:05 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keys_linux.h"

int	hook_close(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_ESC)
	{
    	mlx_destroy_window(cub3d->mlx, cub3d->win);
		exit(0);
	}
	return (0);
}

int	keycode_print(int keycode, t_cub3d *cub3d)
{
	ft_putnbr_fd(keycode, 1);
	ft_putchar_fd('\n', 1);
}

int	hook_ws(int keycode, t_cub3d *cub3d)
{
	// if (keycode == KEY_W)
	// {

	// }
	// else if (keycode == KEY_S)
	// {

	// }
	return (0);
}

int	hook_ad(int keycode, t_cub3d *cub3d)
{
	// if (keycode == KEY_A)
	// {

	// }
	// else if (keycode == KEY_D)
	// {

	// }
	return (0);
}

int	hook_mouse(int keycode, t_cub3d *cub3d)
{
	ft_putnbr_fd(keycode, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
